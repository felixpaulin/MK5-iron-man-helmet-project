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

SerialPort::~SerialPort()
{
    close();
}

bool SerialPort::open()
{
    handle = CreateFileA(
        portName.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (handle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to open " << portName << std::endl;
        handle = nullptr;
        return false;
    }

    DCB serialParams = {};
    serialParams.DCBlength = sizeof(serialParams);

    if (!GetCommState(handle, &serialParams))
    {
        std::cout << "Failed to read COM settings." << std::endl;
        close();
        return false;
    }

    serialParams.BaudRate = CBR_115200;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;

    if (!SetCommState(handle, &serialParams))
    {
        std::cout << "Failed to configure COM port." << std::endl;
        close();
        return false;
    }

    std::cout << "Connected to " << portName << std::endl;

    return true;
}

void SerialPort::close()
{
    if (handle != nullptr)
    {
        CloseHandle(handle);
        handle = nullptr;
    }
}

bool SerialPort::send(const std::string& message)
{
    if (!isOpen())
        return false;

    DWORD bytesWritten;

    BOOL success = WriteFile(
        handle,
        message.c_str(),
        (DWORD)message.length(),
        &bytesWritten,
        nullptr
);

return success && bytesWritten == message.length();
}

bool SerialPort::isOpen() const
{
    return handle != nullptr;
}

