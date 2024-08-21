#ifndef GENERAL_H
#define GENERAL_H

#include <windows.h>
#include <string>

// Function declarations
void SetRegistryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, DWORD data);
void SetRegistryString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& data);
void SetRegistryBinaryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const BYTE* data, DWORD dataSize);
void DeleteRegistryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName);
void DeleteRegistryString(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const std::wstring& value);
void ExecuteCommand(const std::wstring& command);
void StopAndDisableService(const std::wstring& serviceName);
void EnableAndStartService(const std::wstring& serviceName);

// Utility function to ensure the registry key exists
void EnsureRegistryKeyExists(HKEY hKeyRoot, const std::wstring& subKey);

#endif // GENERAL_H
