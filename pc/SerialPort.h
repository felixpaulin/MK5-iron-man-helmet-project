/*
MK5 Iron Man Helmet Controller

File:
   SerialPort.h

Author:
    Felix Paulin


Description:
    Declares the SerialPort class used for USB Serial
    communication between the desktop TinyML application
    and the ESP32 helmet controller.

Responsibilities:
    - Open and close a COM port
    - Send text-based commands
    - Hide Windows-specific serial code from the rest
      of the application

Future Use:
    This class will allow the TinyML listener and future
    desktop applications to control the helmet without
    needing to know how Windows serial communication works.

============================================================
*/

#include <windows.h> 

#pragma once              // Prevents this file from being included twice.

#include <string>         // Lets us use std::string.

class SerialPort {
public:

    // Constructor
    // Called automatically when you write:
    // SerialPort helmet("COM5");
    SerialPort(const std::string& portName);

    // Destructor
    // Called automatically when the object disappears.
    // Used to clean up resources.
    ~SerialPort();

    // Opens the COM port.
    // Returns true if successful.
    bool open();

    // Closes the COM port.
    void close();

    // Sends text over USB.
    // Example:
    // send("SECTION_HELMET\n");
    bool send(const std::string& message);

    // Returns true if the COM port is currently open.
    bool isOpen() const;

private:

    // Stores the COM port name.
    // Example:
    // "COM5"
    std::string portName;

    // Windows uses something called a HANDLE
    // to represent an open device.
    // We keep it private because nobody outside
    // the class should modify it.
    HANDLE handle;
};