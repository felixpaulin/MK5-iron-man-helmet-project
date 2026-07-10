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

    std::cout << "Available Commands\n";
    std::cout << "------------------\n";
    std::cout << "section_helmet\n";
    std::cout << "lock_helmet\n";
    std::cout << "open_helmet\n";
    std::cout << "close_helmet\n";
    std::cout << "exit\n\n";
    
    while (true)
    {
        std::string command;

        std::cout << "> ";

        std::getline(std::cin, command);

        if (command == "exit")
        {
            break;
        }

    if (helmet.send(command + "\n"))
    {
        std::cout << "Sent: " << command << std::endl;
    }
    else
    {
        std::cout << "Failed to send!" << std::endl;
    }

    }
    helmet.close();
    return 0;
}
