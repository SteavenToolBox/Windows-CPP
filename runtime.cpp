#include "runtime.h"
#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <locale>
#include <codecvt>

bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID administratorsGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &administratorsGroup)) {
        CheckTokenMembership(NULL, administratorsGroup, &isAdmin);
        FreeSid(administratorsGroup);
    }

    return isAdmin;
}

void RunAsAdmin() {
    wchar_t szPath[MAX_PATH];
    if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath))) {
        SHELLEXECUTEINFOW sei = { sizeof(sei) };
        sei.lpVerb = L"runas";
        sei.lpFile = szPath;
        sei.hwnd = NULL;
        sei.nShow = SW_NORMAL;

        if (!ShellExecuteExW(&sei)) {
            DWORD dwError = GetLastError();
            if (dwError == ERROR_CANCELLED) {
                std::cerr << "User declined the UAC prompt." << std::endl;
            }
        }
        else {
            ExitProcess(0);
        }
    }
}

void InstallChocolatey() {
    std::cout << "Checking if Chocolatey is installed..." << std::endl;
    if (system("choco -v >nul 2>&1") != 0) {
        std::cout << "Chocolatey is not installed. Installing Chocolatey..." << std::endl;\
        system("powershell -Command \"Set - ExecutionPolicy Bypass - Scope CurrentUser - Force\"");
        system("powershell -Command \"Invoke-WebRequest -Uri https://chocolatey.org/install.ps1 -OutFile C:\\Windows\\Temp\\chocolatey-installer.ps1\"");
        system("powershell -Command \"C:\\Windows\\Temp\\chocolatey-installer.ps1\"");
        system("powershell -Command \"Remove-Item C:\\Windows\\Temp\\chocolatey-installer.ps1\"");
        system("choco feature enable -n=allowGlobalConfirmation -y");
    }
    else {
        std::cout << "Chocolatey is already installed." << std::endl;
    }
    std::cout << "Checking if ChocolateyGUI is installed..." << std::endl;
    if (system("chocolateygui -v>nul 2>&1") != 0) {
        std::cout << "ChocolateyGUI is not installed. Installing ChocolateyGUI..." << std::endl;
        system("choco install chocolateygui -y");
    }
    else {
        std::cout << "ChocolateyGUI is already installed." << std::endl;
        std::cout << "Killing ChocolateyGUI process..." << std::endl;
        system("taskkill /IM chocolateygui.exe /F>nul 2>&1");
    }
}

void InstallWinget() {
    std::cout << "Checking if winget is installed..." << std::endl;
    if (system("where winget") != 0) {
        std::cout << "Winget is not installed. Installing winget..." << std::endl;
        system("choco install winget -y");
    }
    else {
        std::cout << "Winget is already installed." << std::endl;
    }
}

void InstallScoop() {
    std::cout << "Checking if Scoop is installed..." << std::endl;
    if (system("scoop -v >nul 2>&1") != 0) {
        std::cout << "Scoop is not installed. Installing Scoop..." << std::endl;
        system("powershell -Command \"Set - ExecutionPolicy Bypass - Scope CurrentUser - Force\"");
        system("powershell -Command \"Invoke-WebRequest -Uri https://get.scoop.sh -OutFile C:\\Windows\\Temp\\get.scoop.ps1\"");
        system("powershell -Command \"C:\\Windows\\Temp\\get.scoop.ps1 -RunAsAdmin\"");
        system("powershell -Command \"Remove-Item C:\\Windows\\Temp\\get.scoop.ps1\"");
    }
    else {
        std::cout << "scoop is already installed." << std::endl;
    }

    system("powershell -Command \"scoop install git\"");
    system("powershell -Command \"scoop bucket add extras\"");
    system("powershell -Command \"scoop install aria2 wget git grep gsudo\"");
    std::cout << "Aria2, Wget, and Git are now installed." << std::endl;
}

void InstallNuGet() {
    std::cout << "Checking if NuGet is installed..." << std::endl;
    if (system("where nuget") != 0) {
        std::cout << "NuGet is not installed. Installing NuGet..." << std::endl;
        wchar_t* tempPath = nullptr;
        size_t tempPathLen = 0;
        _wdupenv_s(&tempPath, &tempPathLen, L"TEMP");
        std::wstring nugetExePath = std::wstring(tempPath) + L"\\nuget.exe";
        free(tempPath);

        std::wstring nugetUrl = L"https://dist.nuget.org/win-x86-commandline/latest/nuget.exe";
        std::wstring command = L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"Invoke-WebRequest -Uri " + nugetUrl + L" -OutFile " + nugetExePath + L"\"";
        _wsystem(command.c_str());

        wchar_t* programFilesPath = nullptr;
        size_t programFilesPathLen = 0;
        _wdupenv_s(&programFilesPath, &programFilesPathLen, L"ProgramFiles");
        std::wstring nugetDir = std::wstring(programFilesPath) + L"\\NuGet";
        free(programFilesPath);

        command = L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"New-Item -ItemType Directory -Path " + nugetDir + L" -Force\"";
        _wsystem(command.c_str());

        command = L"move /Y " + nugetExePath + L" " + nugetDir + L"\\nuget.exe";
        _wsystem(command.c_str());

        wchar_t* pathEnv = nullptr;
        size_t pathEnvLen = 0;
        _wdupenv_s(&pathEnv, &pathEnvLen, L"PATH");
        std::wstring path = std::wstring(pathEnv) + L";" + nugetDir;
        free(pathEnv);

        SetEnvironmentVariableW(L"Path", path.c_str());
    }
    else {
        std::cout << "NuGet is already installed." << std::endl;
    }
}

void InstallWindowsUpdateCli() {
    std::cout << "Checking if PSWindowsUpdate module is installed..." << std::endl;
    _wsystem(L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"Set-PSRepository -Name 'PSGallery' -InstallationPolicy Trusted\"");
    if (_wsystem(L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"Get-Module -Name PSWindowsUpdate -ListAvailable\"") != 0) {
        _wsystem(L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"Install-Module -Name PSWindowsUpdate -Force\"");
    }

    std::cout << "Checking if WUServiceManager has Microsoft Update configured..." << std::endl;
    if (_wsystem(L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"Get-WUServiceManager | Where-Object { $_.MicrosoftUpdate -eq $true }\"") != 0) {
        _wsystem(L"powershell -NoProfile -ExecutionPolicy Bypass -Command \"Add-WUServiceManager -MicrosoftUpdate\"");
    }
}

void InstallTopgrade() {
    std::cout << "Checking if Topgrade is installed..." << std::endl;
    if (system("topgrade --version") != 0) {
        std::cout << "Topgrade is not installed. Installing Topgrade..." << std::endl;
        system("winget install -e --id topgrade-rs.topgrade");
    }
    else {
        std::cout << "Topgrade is already installed." << std::endl;
    }

    wchar_t* appDataPath = nullptr;
    size_t appDataPathLen = 0;
    _wdupenv_s(&appDataPath, &appDataPathLen, L"APPDATA");
    std::wstring configPath = std::wstring(appDataPath) + L"\\topgrade.toml";
    free(appDataPath);

    std::ifstream configFile(configPath);
    if (configFile.is_open()) {
        std::ofstream tempFile("temp.toml");
        std::string line;
        while (getline(configFile, line)) {
            if (line.find("# enable_winget = true") != std::string::npos) {
                line = "enable_winget = true";
            }
            tempFile << line << std::endl;
        }
        configFile.close();
        tempFile.close();
        _wremove(configPath.c_str());
        _wrename(L"temp.toml", configPath.c_str());
    }
    else {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::cout << "Configuration file not found at " << converter.to_bytes(configPath) << std::endl;
    }
}

void RuntimePowerShell() {
    // Construct the PowerShell command
    std::string command = R"(powershell.exe -Command "irm https://github.com/SteavenToolBox/Windows-CPP/raw/main/runtime.ps1 | iex")";

    // Print the command for debugging
    std::cout << "Executing command: " << command << std::endl;

    // Run the command
    int result = system(command.c_str());

    // Check if the command was successful
    if (result == 0) {
        std::cout << "Script executed successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to execute script." << std::endl;
    }
}
