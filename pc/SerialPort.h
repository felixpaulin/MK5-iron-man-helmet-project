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

#pragma once // Prevents double-inclusion errors

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN // Strips out unneeded Windows APIs
#endif

#include <windows.h>
#include <string>

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
