#include "toolbox.h"
#include <iostream>
#include <string>
#include <windows.h>
#include "SteavenToolBox.h"
#include "runtime.h"

void UpdateWindowsUsingTopgrade() {
    InstallTopgrade();
    std::cout << "Update All Installed Apps to the Latest Versions" << std::endl;

    // Run PowerShell command as admin
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = L"powershell.exe";
        sei.lpParameters = L"topgrade";
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteExW(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                std::cerr << "User declined the UAC prompt." << std::endl;
            }
        }
        else {
            std::cout << "Command executed successfully." << std::endl;
        }
    }
    else {
        std::cerr << "Failed to retrieve executable path." << std::endl;
    }

    system("pause");
    clearScreen(); // Assuming clearScreen() clears the console screen
}
