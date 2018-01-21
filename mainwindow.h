#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include "openscad_interface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void readData();

protected:
    void timerEvent(QTimerEvent *event);

private:
    Ui::MainWindow *ui;
    org::openscad::OpenSCAD* OpenSCAD;
    QSerialPort *m_serial = nullptr;
    int phiRaw;
    int phi;
    int x;
    int y;
    int z;
    int phiOff;
};

#endif // MAINWINDOW_H
