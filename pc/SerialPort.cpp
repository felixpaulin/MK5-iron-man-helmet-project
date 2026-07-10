/*
============================================================

Project:
    MK5 Iron Man Helmet Controller

File:
    SerialPort.cpp

Author:
    Felix Paulin

Description:
    Implements the SerialPort class responsible for
    communicating with the ESP32 over USB Serial.

Responsibilities:
    - Open Windows COM ports
    - Configure serial communication
    - Send commands to the helmet
    - Close the COM port safely

Future Use:
    This file will allow the desktop TinyML listener
    to send recognised voice commands directly to the
    ESP32 helmet controller.

============================================================
*/

#include "SerialPort.h"

#include <windows.h>
#include <iostream>

SerialPort::SerialPort(const std::string& portName)
{
    this->portName = portName;
    this->handle = nullptr;
}