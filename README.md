# openscad-dbus-microbit
## Description
This programm is for mapping a BBC Micro:Bit to the DBus Interface of
OpenSCAD.

## building the linux programm
Building is as simple as
  qmake
  make
  ./microbus

This program is using the QT Modul Serial Port.
You may need a newer qmake then the one supplied with your linux distribution.

## prgogramming the BBC:MicroBit
The source code is found under bbcmicrobit/serialport.js
The code can be compiled under https://makecode.microbit.org/

If you want to skip that step, there is also a hex file provided.

## Technical Details
The BBC Micro:Bit is offering an accelerometer and a magnetometer.
The development enviroment at https://makecode.microbit.org/ allows
for easy acces of the accelerometer data and the compass heading.

The price of this simple implementation is, that both accelerometer and
the compass are very unstable in vertical position.
To get the compass more stable, lower level access to the magento meter
could be used.

## license
Written by Michael Frey <michael.frey@gmx.ch>

## futher read
this is based on
 * https://github.com/MichaelPFrey/openscad-dbus-reference
and 
 * http://doc.qt.io/qt-5/qtserialport-terminal-example.html
 
