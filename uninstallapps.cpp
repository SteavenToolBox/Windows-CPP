#include <windows.h>
#include <iostream>
#include <string>
#include "general.h"
#include "SteavenToolBox.h"


void UninstallApps() {
    std::string choice;

    do {
        clearScreen();
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "0. Go Back\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Some people say removing Edge might break Windows\n";
        std::cout << "So to be safe, just don't remove it.\n";
        std::cout << "1. Uninstall Microsoft Edge\n";
        std::cout << "2. Uninstall Microsoft OneDrive\n";
        std::cout << "3. Uninstall Microsoft Teams\n";
        std::cout << "4. Disable Windows Media Player (Legacy)\n";
        std::cout << "5. Uninstall Cortana\n";
        std::cout << "---------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Type the number: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::cout << "Uninstalling Microsoft Edge...\n";
            system("powershell -Command \"Set - ExecutionPolicy Bypass - Scope CurrentUser - Force\"");
            system("powershell -Command \"Set-ExecutionPolicy Bypass -Scope CurrentUser -Force\"");
            system("powershell -Command \"Add-MpPreference -ExclusionPath 'C:\\Windows\\Temp\\Remove-Edge.exe'\"");
            system("powershell -Command \"Invoke-WebRequest -Uri https://github.com/ShadowWhisperer/Remove-MS-Edge/blob/main/Remove-Edge.exe?raw=true -OutFile C:\\Windows\\Temp\\Remove-Edge.exe\"");
            system("powershell -Command \"Start-Process 'C:\\Windows\\Temp\\Remove-Edge.exe' -Verb RunAs -Wait\"");
            system("powershell -Command \"Remove-Item C:\\Windows\\Temp\\Remove-Edge.exe\"");
            system("powershell -Command \"Remove-MpPreference -ExclusionPath 'C:\\Windows\\Temp\\Remove-Edge.exe'\"");
            system("pause");
        }
        else if (choice == "2") {
            std::cout << "Uninstalling Microsoft OneDrive...\n";
            system("powershell -Command \"Set - ExecutionPolicy Bypass - Scope CurrentUser - Force\"");
            system("powershell -Command \"Set-ExecutionPolicy Bypass -Scope CurrentUser -Force\"");
            system("powershell -Command \"Invoke-WebRequest -Uri https://github.com/SteavenToolBox/Windows/raw/main/Scripts/onedrive-uninstaller.cmd  -OutFile C:\\Windows\\Temp\\onedrive-uninstaller.cmd\"");
            system("powershell -Command \"C:\\Windows\\Temp\\onedrive-uninstaller.cmd\"");
            system("powershell -Command \"Remove-Item C:\\Windows\\Temp\\onedrive-uninstaller.cmd\"");
            system("pause");
        }
        else if (choice == "3") {
            std::cout << "Hiding Teams From Taskbar...\n";
            SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarMn", 0);
            SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarMn", 0);
            std::cout << "Uninstalling Microsoft Teams...\n";
            ExecuteCommand(L"powershell -command \"Get-AppxPackage MicrosoftTeams* | Remove-AppxPackage\"");
            system("pause");
        }
        else if (choice == "4") {
            std::cout << "Disabling Windows Media Player (Legacy)...\n";
            system("powershell -Command \"DISM /online /disable-feature /featurename:WindowsMediaPlayer");
            system("pause");
        }
        else if (choice == "5") {
            std::cout << "Disabling Web Search and Cortana...\n";
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCortana", 0);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCloudSearch", 0);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCortanaAboveLock", 0);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"ConnectedSearchUseWeb", 0);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowSearchToUseLocation", 0);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"DisableWebSearch", 1);
            SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\Explorer", L"DisableSearchBoxSuggestions", 1);
            SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\Explorer", L"DisableSearchBoxSuggestions", 1);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"BingSearchEnabled", 0);
            SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", L"BingSearchEnabled", 0);
            SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton", 0);
            std::cout << "Hiding Cortana From Taskbar...\n";
            SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton", 0);
            std::cout << "Uninstalling Cortana...\n";
            ExecuteCommand(L"powershell -command \"Get-AppxPackage Microsoft.549981C3F5F10 | Remove-AppxPackage\"");
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