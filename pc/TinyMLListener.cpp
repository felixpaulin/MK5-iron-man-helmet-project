/*
============================================================

Project:
    MK5 Iron Man Helmet Controller

File:
    TinyMLListener.cpp

Author:
    Felix Paulin

Description:
    Main desktop application responsible for sending
    commands to the ESP32 helmet controller.

Current Version:
    Keyboard input

Future Versions:
    - Audio capture
    - TinyML wake word detection
    - TinyML command recognition
    - Automatic serial communication

============================================================
*/

#include <iostream>
#include <string>

#include "SerialPort.h"

int main()
{
    std::cout << "=========================================\n";
    std::cout << " MK5 TinyML Desktop Listener\n";
    std::cout << "=========================================\n\n";

    SerialPort helmet("COM5");


    if (!helmet.open())
    {
        std::cout << "Failed to connect to helmet.\n";
        return 1;
    }

    std::cout << "\nConnected successfully!\n\n";

    std::cout << "======== MK5 Helmet Commands (use numbers) ========\n\n";

    std::cout << "[1] Section Helmet\n";
    std::cout << "[2] Lock Helmet\n";
    std::cout << "[3] Open Helmet\n";
    std::cout << "[4] Close Helmet\n";
    std::cout << "[5] Exit\n\n";
    
    while (true)
    {
        std::string command;

        std::cout << "> ";
        std::getline(std::cin, command);

        if (command.empty())
        {
            continue;
        }

if (command == "5")
{
    std::cout << "Closing connection..." << std::endl;
    break;
}

// Convert menu choice into helmet command
std::string serialCommand;

switch (command[0])
{
case '1':
    serialCommand = "section_helmet";
    break;

case '2':
    serialCommand = "lock_helmet";
    break;

case '3':
    serialCommand = "open_helmet";
    break;

case '4':
    serialCommand = "close_helmet";
    break;

default:
    std::cout << "Invalid option!" << std::endl;
    continue;
}

std::cout << "Sending..." << std::endl;

if (helmet.send(serialCommand + "\n"))
{
    std::cout << "Sent: " << serialCommand << std::endl;
}
else
{
    std::cout << "Failed to send!" << std::endl;
}

std::cout << "Done" << std::endl;
    }
    helmet.close();
    std::cout << "Disconnected." << std::endl;
    return 0;
}
