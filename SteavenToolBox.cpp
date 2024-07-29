#include <iostream>
#include <string>
#include <windows.h>
#include <shellapi.h>
#include "runtime.h"
#include "toolbox.h"

void downloadAndExecuteRuntime() {
    RuntimePowerShell();
}

void clearScreen() {
    // Clear the screen by printing enough empty lines to scroll the console
    COORD topLeft = { 0, 0 };
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(consoleHandle, &screen);
    FillConsoleOutputCharacter(consoleHandle, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(consoleHandle, topLeft);
}

int main() {
    bool exitProgram = false;

    do {
        // Check if the program is running as an administrator
        if (!IsRunAsAdmin()) {
            RunAsAdmin();
            return 0; // Exit the current instance as the elevated one will take over
        }

        std::string choice;
        while (true) {
            std::cout << "---------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "1. Install Runtime" << std::endl;
            std::cout << "2. Start Toolbox" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cout << "---------------------------------------------------------------------------------------------------------------------" << std::endl;
            std::cout << "Type the number: ";
            std::getline(std::cin, choice);

            if (choice == "1") {
                downloadAndExecuteRuntime();

                // Pause until the user presses Enter
                std::cout << "Press Enter to continue...";
                std::cin.get(); // Wait for Enter key
                clearScreen(); // Clear the screen

                break; // After installation, break out of the choice loop
            }
            else if (choice == "2") {
                SteavenToolBoxMainMenu();

                // Pause until the user presses Enter
                std::cout << "Press Enter to continue...";
                std::cin.get(); // Wait for Enter key
                clearScreen(); // Clear the screen

                break; // After starting toolbox, break out of the choice loop
            }
            else if (choice == "3") {
                exitProgram = true;
                break; // Exit the main menu loop
            }
            else {
                std::cout << "\"" << choice << "\" is not valid, try again" << std::endl;
                std::cout << std::endl;
            }
        }
    } while (!exitProgram);

    system("pause");
    return 0;
}
