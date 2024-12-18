#include "toolbox.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "SteavenToolBox.h"
#include "crackwindows.h"
#include "optmiusewindows.h"
#include "updatewindows.h"
#include "repairdevices.h"
#include "repairwindows.h"
#include "installprograms.h"
#include "undo.h"
#include "updatefix.h"
#include "uninstallapps.h"



void SteavenToolBoxMainMenu() {
    std::string choice;

    do {
        clearScreen();
        std::cout << "=======================================================================" << std::endl;
        std::cout << "SteavenToolbox | We care about your PC!" << std::endl;
        std::cout << "Windows 10 and Windows 11!" << std::endl;
        std::cout << "=======================================================================" << std::endl;
        std::cout << "-----------------------------------------------------------------------" << std::endl;
        std::cout << "1. Tweak Windows" << std::endl;
        std::cout << "2. Undo Tweaks made by 1" << std::endl;
        std::cout << "3. Update All Installed Apps to the Latest Versions" << std::endl;
        std::cout << "4. Install Features, Programs, and Apps" << std::endl;
        std::cout << "5. Windows Update Fix" << std::endl;
        std::cout << "6. Crack Windows and Office (Use it at your own risk)" << std::endl;
        std::cout << "7. Uninstall Apps" << std::endl;
        std::cout << "8. Repair Windows" << std::endl;
        std::cout << "9. Repair Broken Storage Disks" << std::endl;
        std::cout << "0. Go Back" << std::endl;
        std::cout << "-----------------------------------------------------------------------" << std::endl;
        std::cout << "Type the number: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            clearScreen();
            OptmiuseWindows(); // Corrected the function name
            system("pause");
        }
        else if (choice == "2") {
            clearScreen();
            UndoWindows(); // Corrected the function name
            system("pause");
        }
        else if (choice == "3") {
            clearScreen();
            UpdateWindowsUsingTopgrade();
        }
        else if (choice == "4") {
            clearScreen();
            InstallPrograms();
        }
        else if (choice == "5") {
            clearScreen();
            UpdateFix();
        }
        else if (choice == "6") {
            crackWindowsAndOffice(); // Call crack function
        }
        else if (choice == "7") {
            clearScreen();
            UninstallApps();
        }
        else if (choice == "8") {
            std::cout << "Repairing Windows..." << std::endl;
            RepairWindows();
            system("pause");
        }
        else if (choice == "9") {
            clearScreen();
            std::cout << "Repairing Broken Storage Disks..." << std::endl;
            RepairDrives();
            system("pause");
        }
        else if (choice == "0") {
            std::cout << "Going back..." << std::endl;
            return;
        }
        else {
            std::cout << "\"" << choice << "\" is not valid, try again" << std::endl;
            std::cout << std::endl;
            system("pause");
        }
    } while (true);
}