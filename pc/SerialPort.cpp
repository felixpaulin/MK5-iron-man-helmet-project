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
        0,                  // Exclusive access
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

    // Allocate Windows serial buffers
    if (!SetupComm(handle, 4096, 4096))
    {
        std::cout << "Warning: Failed to allocate serial buffers."
                  << std::endl;
    }

    // Read current COM settings
    DCB serialParams = {};
    serialParams.DCBlength = sizeof(serialParams);

    if (!GetCommState(handle, &serialParams))
    {
        std::cout << "Failed to read COM settings." << std::endl;
        close();
        return false;
    }

    // Configure serial settings
    serialParams.BaudRate = CBR_115200;
    serialParams.ByteSize = 8;
    serialParams.StopBits = ONESTOPBIT;
    serialParams.Parity   = NOPARITY;

    if (!SetCommState(handle, &serialParams))
    {
        std::cout << "Failed to configure COM port." << std::endl;
        close();
        return false;
    }

    // Clear old data from previous sessions
    if (!PurgeComm(
            handle,
            PURGE_RXCLEAR |
            PURGE_TXCLEAR |
            PURGE_RXABORT |
            PURGE_TXABORT))
    {
        std::cout << "Warning: Failed to purge serial buffers."
                  << std::endl;
    }

    // Configure timeouts
    COMMTIMEOUTS timeouts = {};

    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(handle, &timeouts))
    {
        std::cout << "Failed to configure COM timeouts."
                  << std::endl;
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
    {
        std::cout << "Serial port is not open." << std::endl;
        return false;
    }

    // Clear any previous communication errors
    DWORD errors = 0;
    COMSTAT status = {};

    if (!ClearCommError(handle, &errors, &status))
    {
        DWORD lastError = GetLastError();

        std::cout << "==========================" << std::endl;
        std::cout << "ClearCommError FAILED!" << std::endl;
        std::cout << "Windows Error Code: " << lastError << std::endl;
        std::cout << "==========================" << std::endl;

        return false;
    }

    std::cout << "Errors: " << errors << std::endl;
    std::cout << "RX Queue: " << status.cbInQue << std::endl;
    std::cout << "TX Queue: " << status.cbOutQue << std::endl;

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
        DWORD error = GetLastError();

        std::cout << "WriteFile failed!" << std::endl;
        std::cout << "Windows Error Code: "
                  << error
                  << std::endl;

        return false;
    }

    if (bytesWritten != message.length())
    {
        std::cout << "Warning: Only "
                  << bytesWritten
                  << " of "
                  << message.length()
                  << " bytes were written."
                  << std::endl;

        return false;
    }

    return true;
}

bool SerialPort::isOpen() const
{
    return handle != nullptr;
}