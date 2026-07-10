#pragma once

#include <string>
#include <windows.h>

/*
============================================================

Project:
    MK5 Iron Man Helmet Controller

File:
    SerialPort.h

Author:
    Felix Paulin

Description:
    Declares the SerialPort class responsible for USB
    Serial communication between the desktop TinyML
    application and the ESP32 helmet controller.

Responsibilities:
    - Open and close a COM port
    - Send text-based commands
    - Hide Windows-specific serial communication
      from the rest of the application

Future Use:
    This class will be used by the desktop TinyML
    listener to send voice commands to the helmet
    over USB Serial.

============================================================
*/

class SerialPort
{
public:
    SerialPort(const std::string& portName);
    ~SerialPort();

    bool open();
    void close();

    bool send(const std::string& message);

    bool isOpen() const;

private:
    std::string portName;
    HANDLE handle;
};