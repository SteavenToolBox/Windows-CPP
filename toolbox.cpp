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



void SteavenToolBoxMainMenu() {
    std::string choice;

    do {
        clearScreen();
        std::cout << "=======================================================================" << std::endl;
        std::cout << "SteavenToolbox | We care about your PC!" << std::endl;
        std::cout << "Windows 10 and Windows 11!" << std::endl;
        std::cout << "=======================================================================" << std::endl;
        std::cout << "-----------------------------------------------------------------------" << std::endl;
        std::cout << "1. Optimize Windows" << std::endl;
        std::cout << "2. Update All Installed Apps to the Latest Versions" << std::endl;
        std::cout << "3. Install Features, Programs, and Apps" << std::endl;
        std::cout << "4. Windows Update Fix" << std::endl;
        std::cout << "5. Crack Windows and Office (Use it at your own risk)" << std::endl;
        std::cout << "6. Uninstall Apps" << std::endl;
        std::cout << "7. Repair Windows" << std::endl;
        std::cout << "8. Repair Broken Storage Disks" << std::endl;
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
            UpdateWindowsUsingTopgrade();
        }
        else if (choice == "3") {
            clearScreen();
            InstallPrograms();
        }
        else if (choice == "4") {
            std::cout << "Fixing Windows Update..." << std::endl;
            std::cout << "Went to fix Windows update" << std::endl; // Replace with actual fix code
            system("pause");
        }
        else if (choice == "5") {
            crackWindowsAndOffice(); // Call crack function
        }
        else if (choice == "6") {
            std::cout << "Uninstalling apps..." << std::endl;
            std::cout << "Went to uninstall apps" << std::endl; // Replace with actual uninstall code
            system("pause");
        }
        else if (choice == "7") {
            std::cout << "Repairing Windows..." << std::endl;
            RepairWindows();
            system("pause");
        }
        else if (choice == "8") {
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