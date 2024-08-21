#include <windows.h>
#include <iostream>
#include <string>

void EnsureRegistryKeyExists(HKEY hKeyRoot, const std::wstring& subKey) {
    HKEY hKey;
    LONG result = RegCreateKeyEx(hKeyRoot, subKey.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, nullptr, &hKey, nullptr);
    if (result == ERROR_SUCCESS) {
        RegCloseKey(hKey);
    }
    else {
        std::wcerr << L"Failed to create registry key: " << subKey << L" with error code: " << result << std::endl;
    }
}

void SetRegistryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, DWORD data) {
    EnsureRegistryKeyExists(hKeyRoot, subKey); // Ensure the key exists

    HKEY hKey;
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        LONG result = RegSetValueEx(hKey, valueName.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*>(&data), sizeof(data));
        RegCloseKey(hKey);
        if (result != ERROR_SUCCESS) {
            std::wcerr << L"Failed to set registry value: " << valueName << L" with error code: " << result << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to open registry key: " << subKey << std::endl;
    }
}

void SetRegistryString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& data) {
    EnsureRegistryKeyExists(hKeyRoot, subKey); // Ensure the key exists

    HKEY hKey;
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        LONG result = RegSetValueEx(hKey, valueName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(data.c_str()), (data.size() + 1) * sizeof(wchar_t));
        RegCloseKey(hKey);
        if (result != ERROR_SUCCESS) {
            std::wcerr << L"Failed to set registry value: " << valueName << L" with error code: " << result << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to open registry key: " << subKey << std::endl;
    }
}

void ExecuteCommand(const std::wstring& command) {
    _wsystem(command.c_str());
}

void StopAndDisableService(const std::wstring& serviceName) {
    SC_HANDLE scManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (scManager) {
        SC_HANDLE service = OpenService(scManager, serviceName.c_str(), SERVICE_STOP | SERVICE_CHANGE_CONFIG);
        if (service) {
            SERVICE_STATUS status;
            ControlService(service, SERVICE_CONTROL_STOP, &status);
            ChangeServiceConfig(service, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
            CloseServiceHandle(service);
        }
        CloseServiceHandle(scManager);
    }
}

void SetRegistryBinaryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const BYTE* data, DWORD dataSize) {
    EnsureRegistryKeyExists(hKeyRoot, subKey); // Ensure the key exists

    HKEY hKey;
    LONG result = RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey);
    if (result == ERROR_SUCCESS) {
        result = RegSetValueEx(hKey, valueName.c_str(), 0, REG_BINARY, data, dataSize);
        RegCloseKey(hKey);
        if (result != ERROR_SUCCESS) {
            std::wcerr << L"Failed to set registry value: " << valueName << L" with error code: " << result << std::endl;
        }
    }
    else {
        std::wcerr << L"Failed to open registry key: " << subKey << std::endl;
    }
}

void DeleteRegistryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName) {
    HKEY hKey;
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegDeleteValue(hKey, valueName.c_str());
        RegCloseKey(hKey);
    }
}

void DeleteRegistryString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& value) {
    HKEY hKey;
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, valueName.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(), (value.size() + 1) * sizeof(wchar_t));
        RegCloseKey(hKey);
    }
}

void EnableAndStartService(const std::wstring& serviceName) {
    SC_HANDLE scManager = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (scManager) {
        SC_HANDLE service = OpenService(scManager, serviceName.c_str(), SERVICE_START | SERVICE_CHANGE_CONFIG);
        if (service) {
            // Change the service configuration to enable it (automatic start)
            ChangeServiceConfig(service, SERVICE_NO_CHANGE, SERVICE_AUTO_START, SERVICE_NO_CHANGE, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);

            // Start the service
            StartService(service, 0, nullptr);

            CloseServiceHandle(service);
        }
        CloseServiceHandle(scManager);
    }
}