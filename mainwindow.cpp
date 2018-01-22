#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>  
#include <iostream>

#define PI 3.14159265

double constrainAngle(double x){
    x = fmod(x,360);
    if (x < 0)
        x += 360;
    return x;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    OpenSCAD = new org::openscad::OpenSCAD("org.openscad.OpenSCAD", "/org/openscad/OpenSCAD/Application",
                           QDBusConnection::sessionBus(), this);
    m_serial=(new QSerialPort(this));
    m_serial->setPortName("/dev/ttyACM0");
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite)) {
        ui->labelDBus->setText("connected");
   } else {
        ui->labelDBus->setText("could not connect");
    }
    x=0;
    y=0;
    z=0;
    phi=0;
    phiOff=0;
    startTimer(100);
	aButton = false;
	bButton = false;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerEventSerial()));
    timer->start(25);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    if (OpenSCAD->isValid())
        ui->labelDBus->setText("connected");
    else
        ui->labelDBus->setText("disconnected");

	if(aButton){
		ui->labelAButton->setText("A Button\nPressed");
	}else{
		ui->labelAButton->setText("A Button\n");
	}

	if(bButton){
		ui->labelBButton->setText("B Button\nPressed");
	}else{
		ui->labelBButton->setText("B Button\n");
	}

	ui->progressBarPhi->setValue(phiRaw);
	ui->progressBarX->setValue(x);
	ui->progressBarY->setValue(y);
	ui->progressBarZ->setValue(z);

	ui->progressBarA->setValue(a);
	ui->progressBarB->setValue(b);
	ui->progressBarC->setValue(c);
}

void MainWindow::timerEventSerial(){
    char buf[1024];

    while(m_serial->canReadLine()){
        m_serial->readLine(buf, sizeof(buf));

        QString line =  QString(buf);
		QStringList elemts = line.split(":");
		QString el = elemts[0];

		if(el=="phi"){
			phiRaw=elemts[1].toInt();
		}else if(el=="x"){
			x=elemts[1].toInt();
		}else if(el=="y"){
			y=elemts[1].toInt();
		}else if(el=="z"){
			z=elemts[1].toInt();
		}else if(el=="A"){
			aButton = (elemts[1].contains("true",Qt::CaseInsensitive));
		}else if(el=="B"){
			bButton = (elemts[1].contains("true",Qt::CaseInsensitive));
		}
   }
	if(aButton){
		phiOff = phiRaw;
	}
	phi = phiRaw - phiOff;

	double xs = cos(phi*PI/180) * x + sin(phi*PI/180) * y;
	double ys = sin(phi*PI/180) * x + cos(phi*PI/180) * y;
	
	//https://www.nxp.com/docs/en/application-note/AN3461.pdf
	a = atan2(+ys,  -z)/PI*180.0;
	b = atan2(+xs,  sqrt(pow(ys,2.0)+pow(z,2.0)))/PI*180.0;
	c = -phi;

	if(z>0){
		a =-a;
	}

	a = constrainAngle(a);
	b = constrainAngle(b);
	c = constrainAngle(c);

	OpenSCAD->rotateTo(a,b,c);
}
void MainWindow::readData()
{

}
