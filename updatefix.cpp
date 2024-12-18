#include <windows.h>
#include <iostream>
#include <string>
#include "general.h"
#include "SteavenToolBox.h"


void UpdateFix() {
    std::string choice;

    do {
        clearScreen();
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "0. Go Back\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "1. Get Windows 11 on unsupported devices\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Choose the build that you are running right now\n";
        std::cout << "2. 24H2 (Works only on Windows 11)\n";
        std::cout << "3. 22H2 (Works on Windows 10/11)\n";
        std::cout << "4. 21H2 (Works on Windows 10/11)\n";
        std::cout << "5. 1809 (Works only on Windows 10)\n";
        std::cout << "6. Undo\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Choose If you want to get feature updates and security updates or security updates only\n";
        std::cout << "7. Security Updates only\n";
        std::cout << "8. Security and feature updates\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Type the number: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::cout << "Applying bypass for Windows 11 on unsupported devices...\n";
            system("powershell -Command \"Set - ExecutionPolicy Bypass - Scope CurrentUser - Force\"");
            system("powershell -Command \"Set-ExecutionPolicy Bypass -Scope CurrentUser -Force\"");
            system("powershell -Command \"Invoke-WebRequest -Uri https://github.com/AveYo/MediaCreationTool.bat/raw/main/bypass11/Skip_TPM_Check_on_Dynamic_Update.cmd -OutFile C:\\Windows\\Temp\\Skip_TPM_Check_on_Dynamic_Update.cmd\"");
            system("powershell -Command \"C:\\Windows\\Temp\\Skip_TPM_Check_on_Dynamic_Update.cmd\"");
            system("powershell -Command \"Remove-Item C:\\Windows\\Temp\\Skip_TPM_Check_on_Dynamic_Update.cmd\"");
        }
        else if (choice == "2") {
            std::cout << "Setting TargetReleaseVersion to 24H2...\n";
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersion", L"1");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersionInfo", L"24H2");
            system("pause");
        }
        else if (choice == "3") {
            std::cout << "Setting TargetReleaseVersion to 22H2...\n";
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersion", L"1");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersionInfo", L"22H2");
            system("pause");
        }
        else if (choice == "4") {
            std::cout << "Setting TargetReleaseVersion to 21H2...\n";
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersion", L"1");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersionInfo", L"21H2");
            system("pause");
        }
        else if (choice == "5") {
            std::cout << "Setting TargetReleaseVersion to 1809...\n";
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersion", L"1");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersionInfo", L"1809");
            system("pause");
        }
        else if (choice == "6") {
            std::cout << "Undoing TargetReleaseVersion settings...\n";
            DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersion");
            DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate", L"TargetReleaseVersionInfo");
            system("pause");
        }
        else if (choice == "7") {
            std::cout << "Setting Windows Update to Get security updates only...\n";
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"AllowAutoWindowsUpdateDownloadOverMeteredNetwork", L"0");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"DeferFeatureUpdatesPeriodInDays", L"869");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"DeferQualityUpdatesPeriodInDays", L"4");
            SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"BranchReadinessLevel", L"32");
            system("pause");
        }
        else if (choice == "8") {
            std::cout << "Setting Windows Update to Get security and feature updates...\n";
            DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"AllowAutoWindowsUpdateDownloadOverMeteredNetwork");
            DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"DeferFeatureUpdatesPeriodInDays");
            DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"DeferQualityUpdatesPeriodInDays");
            DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\WindowsUpdate\\UX\\Settings", L"BranchReadinessLevel");
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