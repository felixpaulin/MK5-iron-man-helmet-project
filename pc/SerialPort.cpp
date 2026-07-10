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
        0, // Exclusive access
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

    // 1. Properly pull existing device configuration parameters first
    DCB serialParams = { 0 };
    serialParams.DCBlength = sizeof(serialParams);
    
    if (!GetCommState(handle, &serialParams))
    {
        std::cout << "Failed to read COM settings." << std::endl;
        close();
        return false;
    }

    // 2. Apply your specific hardware overrides cleanly
    serialParams.BaudRate = CBR_115200; // Assumes 115200 in ESP code
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity = NOPARITY;

    if (!SetCommState(handle, &serialParams))
    {
        std::cout << "Failed to configure COM port." << std::endl;
        close();
        return false;
    }

    // 3. Apply standard, non-blocking time policies to prevent packet hanging
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50; 
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(handle, &timeouts))
    {
        std::cout << "Failed to set serial timeouts." << std::endl;
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

    DWORD bytesWritten = 0;

    BOOL success = WriteFile(
        handle,
        message.c_str(),
        static_cast<DWORD>(message.length()),
        &bytesWritten,
        nullptr
    );

    if (!success)
    {
        std::cout << "WriteFile failed. Error: " << GetLastError() << std::endl;
        return false;
    }

    // Flush makes sure everything is physically gone down the wire
    FlushFileBuffers(handle);

    return (bytesWritten == message.length());
}

bool SerialPort::isOpen() const
{
    return handle != nullptr;
}
