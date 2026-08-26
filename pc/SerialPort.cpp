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
    DWORD error = GetLastError();

    std::cout << "==========================" << std::endl;
    std::cout << "FAILED TO OPEN SERIAL PORT" << std::endl;
    std::cout << "Port: " << portName << std::endl;
    std::cout << "Windows Error Code: " << error << std::endl;

    if (error == ERROR_ACCESS_DENIED)
    {
        std::cout << "Meaning: ACCESS DENIED (Error 5)" << std::endl;
    }
    else if (error == ERROR_FILE_NOT_FOUND)
    {
        std::cout << "Meaning: PORT NOT FOUND (Error 2)" << std::endl;
    }
    else
    {
        std::cout << "Meaning: Unknown Windows error" << std::endl;
    }

    std::cout << "==========================" << std::endl;

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

    // Check the current communication state
    DWORD errors = 0;
    COMSTAT status = {};

    BOOL clearResult = ClearCommError(handle, &errors, &status);
    DWORD clearError = clearResult ? ERROR_SUCCESS : GetLastError();

    std::cout << "\n==========================" << std::endl;
    std::cout << "SERIAL DEBUG" << std::endl;
    std::cout << "ClearCommError result: "
              << (clearResult ? "SUCCESS" : "FAILED")
              << std::endl;
    std::cout << "ClearCommError Windows error: "
              << clearError
              << std::endl;
    std::cout << "Communication errors: "
              << errors
              << std::endl;
    std::cout << "RX Queue: "
              << status.cbInQue
              << std::endl;
    std::cout << "TX Queue: "
              << status.cbOutQue
              << std::endl;
    std::cout << "==========================" << std::endl;

    if (!clearResult)
    {
        return false;
    }

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

        std::cout << "==========================" << std::endl;
        std::cout << "WriteFile FAILED!" << std::endl;
        std::cout << "Windows Error Code: "
                  << error
                  << std::endl;
        std::cout << "==========================" << std::endl;

        return false;
    }

    std::cout << "WriteFile succeeded: "
              << bytesWritten
              << " bytes written."
              << std::endl;

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