#include <windows.h>
#include <iostream>
#include <string>

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

void SetRegistryBinaryValue(HKEY hKeyRoot, const std::wstring& subKey, const std::wstring& valueName, const BYTE* data, DWORD dataSize) {
    HKEY hKey;
    if (RegOpenKeyEx(hKeyRoot, subKey.c_str(), 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueEx(hKey, valueName.c_str(), 0, REG_BINARY, data, dataSize);
        RegCloseKey(hKey);
    }
}

void ExecuteCommand(const std::wstring& command) {
    _wsystem(command.c_str());
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

void UndoWindows() {
    std::wcout << L"Disabling Web Search and Cortana\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCortana");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCloudSearch");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCortanaAboveLock");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"ConnectedSearchUseWeb");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowSearchToUseLocation");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"DisableWebSearch");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\Explorer", L"DisableSearchBoxSuggestions");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Policies\\Microsoft\\Windows\\Explorer", L"DisableSearchBoxSuggestions");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"BingSearchEnabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", L"BingSearchEnabled");

    std::wcout << L"Hiding Cortana From Taskbar\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton");

    std::wcout << L"Hiding Teams Icon From Taskbar\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarMn");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarMn");

    std::wcout << L"Disabling Telemetry\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"AllowTelemetry");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"DoNotShowFeedbackNotifications");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection", L"AllowTelemetry");

    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Application Experience\\Microsoft Compatibility Appraiser\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Application Experience\\ProgramDataUpdater\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Autochk\\Proxy\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\Consolidator\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\UsbCeip\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\DiskDiagnostic\\Microsoft-Windows-DiskDiagnosticDataCollector\" /Disable>nul");

    std::wcout << L"Disabling Wi-Fi Sense\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\PolicyManager\\default\\Wifi\\AllowAutoConnectToWiFiSenseHotspots", L"value");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\PolicyManager\\default\\Wifi\\AllowWiFiHotSpotReporting", L"value");

    std::wcout << L"Disabling Application suggestions\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"ContentDeliveryAllowed");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"OemPreInstalledAppsEnabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"PreInstalledAppsEnabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"PreInstalledAppsEverEnabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SilentInstalledAppsEnabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338387Enabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338388Enabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353698Enabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338393Enabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353694Enabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353696Enabled");

    std::wcout << L"Disabling Activity History\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"EnableActivityFeed");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"PublishUserActivities");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"UploadUserActivities");

    std::wcout << L"Disabling Location Tracking\n";
    DeleteRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location", L"Value", L"Deny");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Sensor\\Overrides\\{BFA794E4-F964-4FDB-90F6-51056BFE4B44}", L"SensorPermissionState");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\lfsvc\\Service\\Configuration", L"Status");

    std::wcout << L"Disabling Feedback\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Siuf\\Rules", L"NumberOfSIUFInPeriod");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClient\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClientOnScenarioDownload\" /Disable>nul");
    EnableAndStartService(L"DiagTrack");
    EnableAndStartService(L"dmwappushservice");

    std::wcout << L"Disabling Advertising ID\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", L"Enabled");

    std::wcout << L"Disabling Error reporting\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting", L"Disabled");
    
    std::wcout << L"Restricting Windows Update P2P only to local network\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization\\Config", L"DODownloadMode");

    std::wcout << L"Stopping and disabling Diagnostics Tracking Service\n";
    EnableAndStartService(L"DiagTrack");

    std::wcout << L"Stopping and disabling WAP Push Service\n";
    EnableAndStartService(L"dmwappushservice");

    std::wcout << L"Enabling F8 boot menu options\n";
    ExecuteCommand(L"%SystemRoot%\\System32\\bcdedit.exe /set {current} bootmenupolicy Legacy>nul");

    std::wcout << L"Stopping and disabling Home Groups services\n";
    EnableAndStartService(L"HomeGroupListener");
    EnableAndStartService(L"HomeGroupProvider");

    std::wcout << L"Disabling Remote Assistance\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Remote Assistance", L"fAllowToGetHelp");

    std::wcout << L"Enabling Hibernation\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Power", L"HibernateEnabled");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FlyoutMenuSettings", L"ShowHibernateOption");

    std::wcout << L"Showing file operations details\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\OperationStatusManager", L"EnthusiastMode");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\OperationStatusManager", L"EnthusiastMode");

    std::wcout << L"Hiding Cortana Button\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton");

    std::wcout << L"Hiding Task View button\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowTaskViewButton");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowTaskViewButton");

    std::wcout << L"Hiding People icon\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\People", L"PeopleBand");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\People", L"PeopleBand");

    std::wcout << L"Hide tray icons\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"EnableAutoTray");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"EnableAutoTray");

    std::wcout << L"Enabling NumLock after startup\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Keyboard", L"InitialKeyboardIndicators");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Control Panel\\Keyboard", L"InitialKeyboardIndicators");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Keyboard", L"InitialKeyboardIndicators", L"2");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Keyboard", L"InitialKeyboardIndicators", L"2");

    std::wcout << L"Changing default Explorer view to This PC\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"LaunchTo");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"LaunchTo");

    std::wcout << L"Improving System Responsiveness using regedit\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"NetworkThrottlingIndex");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"SystemResponsiveness");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control", L"WaitToKillServiceTimeout");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"AutoEndTasks", L"1");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"AutoEndTasks", L"1");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"HungAppTimeout", L"1000");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"HungAppTimeout", L"1000");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"MenuShowDelay", L"1");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"MenuShowDelay", L"1");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"WaitToKillAppTimeout", L"2000");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"WaitToKillAppTimeout", L"2000");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"LowLevelHooksTimeout", L"1000");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"LowLevelHooksTimeout", L"1000");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseHoverTime", L"400");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseHoverTime", L"400");
    DeleteRegistryString(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control", L"WaitToKillServiceTimeout", L"2000");

    std::wcout << L"Disabling Sync Provider Notifications\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowSyncProviderNotifications");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowSyncProviderNotifications");
    
    std::wcout << L"Disabling Subscribed Content 338387\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338387Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338387Enabled");

    std::wcout << L"Disabling Subscribed Content 338393\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338393Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338393Enabled");
    
    std::wcout << L"Disabling Subscribed Content 310093\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-310093Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-310093Enabled");
    
    std::wcout << L"Disabling Subscribed Content 338389\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled");
    
    std::wcout << L"Disabling Subscribed Content 314563\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-314563Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-314563Enabled");
    
    std::wcout << L"Disabling Soft Landing\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SoftLandingEnabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SoftLandingEnabled");
    
    std::wcout << L"Disabling Scoobe System Setting\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\UserProfileEngagement", L"ScoobeSystemSettingEnabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\UserProfileEngagement", L"ScoobeSystemSettingEnabled");
    
    std::wcout << L"Disabling Silent Installed Apps\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SilentInstalledAppsEnabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SilentInstalledAppsEnabled");
    
    std::wcout << L"Disabling Advertising Info\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", L"Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", L"Enabled");
    
    std::wcout << L"Disabling Tailored Experiences with Diagnostic Data\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Privacy", L"TailoredExperiencesWithDiagnosticDataEnabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Privacy", L"TailoredExperiencesWithDiagnosticDataEnabled");
    
    std::wcout << L"Enabling Periodic Backup\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Configuration Manager", L"EnablePeriodicBackup");

    std::wcout << L"Disabling Shortcut Arrow Icon\n";
    BYTE binaryData[] = { 0x00, 0x00, 0x00, 0x00 };
    SetRegistryBinaryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"link", binaryData, sizeof(binaryData));
    SetRegistryBinaryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"link", binaryData, sizeof(binaryData));
    
    std::wcout << L"Enabling Expressive Input Shell Hotkey\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Input\\Settings", L"EnableExpressiveInputShellHotkey");

    std::wcout << L"Disabling New App Alert\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Explorer", L"NoNewAppAlert");

    std::wcout << L"Enabling Display Parameters\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\CrashControl", L"DisplayParameters");

    std::wcout << L"Adding Install this update to CABFolder Shell\n";
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CABFolder\\Shell\\RunAs", L"", L"Install this update");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CABFolder\\Shell\\RunAs", L"HasLUAShield", L"");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CABFolder\\Shell\\RunAs\\Command", L"", L"cmd /k dism /online /add-package /packagepath:\"%%1\"");

    std::wcout << L"Adding Kill not responding tasks to DesktopBackground Shell\n";
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"", L"Kill not responding tasks");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"icon", L"taskmgr.exe,-30651");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"MUIVerb", L"Kill not responding tasks");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"Position", L"Top");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding\\command", L"", L"cmd.exe /K taskkill.exe /F /FI \"status eq NOT RESPONDING\"");

    std::wcout << L"Adding Personalization to CLSID\n";
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"", L"@%SystemRoot%\\System32\\themecpl.dll,-1#immutable1");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"InfoTip", L"@%SystemRoot%\\System32\\themecpl.dll,-2#immutable1");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"System.ApplicationName", L"Microsoft.Personalization");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"System.Software.TasksFileUrl", L"Internal");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}\\DefaultIcon", L"", L"%SystemRoot%\\System32\\themecpl.dll,-1");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}\\Shell\\Open\\command", L"", L"explorer shell:::{ED834ED6-4B5A-4bfe-8F11-A626DCB6A921}");
    DeleteRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ControlPanel\\NameSpace\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"", L"Personalization");
   
    std::wcout << L"Adding Windows Update to CLSID\n";
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"System.Software.TasksFileUrl", L"Internal");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"System.ApplicationName", L"Microsoft.WindowsUpdate");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"System.ControlPanel.Category", L"5");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"", L"@%SystemRoot%\\system32\\shell32.dll,-22068");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"InfoTip", L"@%SystemRoot%\\system32\\shell32.dll,-22580");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}\\DefaultIcon", L"", L"shell32.dll,-47");
    DeleteRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}\\Shell\\Open\\Command", L"", L"control.exe /name Microsoft.WindowsUpdate");
    DeleteRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ControlPanel\\NameSpace\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"", L"Windows Update");

    std::wcout << L"Disabling Shortcut Arrow Icon for Current User\n";
    BYTE zeroData[] = { 0x00, 0x00, 0x00, 0x00 };
    SetRegistryBinaryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"link", zeroData, sizeof(zeroData));

    std::wcout << L"Disabling Shortcut Arrow Icon for Default User\n";
    SetRegistryBinaryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"link", zeroData, sizeof(zeroData));

    std::wcout << L"Disabling Tailored Experiences with Diagnostic Data for Current User\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableTailoredExperiencesWithDiagnosticData");

    std::wcout << L"Disabling Tailored Experiences with Diagnostic Data for Default User\n";
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableTailoredExperiencesWithDiagnosticData");

    std::wcout << L"Enabling Long Paths\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\FileSystem", L"LongPathsEnabled");
    
    std::wcout << L"Configuring Driver Search Order\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", L"SearchOrderConfig");

    std::wcout << L"Setting System Responsiveness\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"SystemResponsiveness");

    std::wcout << L"Disabling Network Throttling\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"NetworkThrottlingIndex");

    std::wcout << L"Disabling Clear Page File at Shutdown\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"ClearPageFileAtShutdown");

    std::wcout << L"Setting NDU Service Start to Automatic\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Services\\Ndu", L"Start");

    std::wcout << L"Setting IRPStackSize\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\LanmanServer\\Parameters", L"IRPStackSize");

    std::wcout << L"Disabling Windows Feeds for Current User\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Feeds", L"EnableFeeds");

    std::wcout << L"Setting Shell Feeds Taskbar View Mode for Current User\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Feeds", L"ShellFeedsTaskbarViewMode");

    std::wcout << L"Hiding Meet Now for Current User\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", L"HideSCAMeetNow");

    std::wcout << L"Disabling Windows Feeds for Default User\n";
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\Windows Feeds", L"EnableFeeds");

    std::wcout << L"Setting Shell Feeds Taskbar View Mode for Default User\n";
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Feeds", L"ShellFeedsTaskbarViewMode");

    std::wcout << L"Hiding Meet Now for Default User\n";
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", L"HideSCAMeetNow");

    std::wcout << L"Setting GPU Priority for Games\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"GPU Priority");

    std::wcout << L"Setting Priority for Games\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"Priority");

    std::wcout << L"Setting Scheduling Category for Games\n";
    DeleteRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"Scheduling Category", L"High");

    std::wcout << L"Disabling sound for Sticky Keys, Toggle Keys, and Filter Keys\n";
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\StickyKeys", L"SOUND", L"");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\StickyKeys", L"SOUND", L"");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\ToggleKeys", L"SOUND", L"");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\ToggleKeys", L"SOUND", L"");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\Keyboard Response", L"SOUND", L"");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\Keyboard Response", L"SOUND", L"");

    std::wcout << L"Disabling warning messages for Sticky Keys, Toggle Keys, and Filter Keys\n";
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\StickyKeys", L"Warning", L"0");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\StickyKeys", L"Warning", L"0");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\ToggleKeys", L"Warning", L"0");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\ToggleKeys", L"Warning", L"0");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\Keyboard Response", L"Warning", L"0");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\Keyboard Response", L"Warning", L"0");

    std::wcout << L"Disabling mouse acceleration\n";
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseSpeed", L"0");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseSpeed", L"0");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold1", L"0");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseThreshold1", L"0");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold2", L"0");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseThreshold2", L"0");

    std::wcout << L"Enabling pointer shadow\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseShadow");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseShadow");

    std::wcout << L"Disabling showing frequently used folders in Quick Access\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"ShowFrequent");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"ShowFrequent");

    std::wcout << L"Showing hidden files in File Explorer\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"Hidden");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"Hidden");

    std::wcout << L"Showing file extensions for unknown file types\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideFileExt");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideFileExt");

    std::wcout << L"Setting Windows Explorer to launch folders in a separate process\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"SeparateProcess");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"SeparateProcess");

    std::wcout << L"Enabling check boxes for file and folder selection in File Explorer\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"CheckFileExtensions");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"CheckFileExtensions");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"AutoCheckSelect");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"AutoCheckSelect");

    std::wcout << L"Showing all folders and libraries in File Explorer\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowAllFolders");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowAllFolders");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowLibraries");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowLibraries");

    std::wcout << L"Setting indexing options to index the entire C: drive\n";
    DeleteRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Search\\CrawlScopeManager\\Windows\\SystemIndex\\DefaultRules", L"0", L"C:\\");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Search\\CrawlScopeManager\\Windows\\SystemIndex\\DefaultRules", L"1");

    std::wcout << L"Tweaking Desktop Icons\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideIcons");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideIcons");
    DeleteRegistryString(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"AutoArrange", L"1");
    DeleteRegistryString(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"AutoArrange", L"1");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"FFLAGS");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"FFLAGS");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}");

    std::wcout << L"Setting dark mode\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"AppsUseLightTheme");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"AppsUseLightTheme");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"SystemUsesLightTheme");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"SystemUsesLightTheme");

    std::wcout << L"Enabling end task in taskbar\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\TaskbarDeveloperSettings", L"TaskbarEndTask");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\TaskbarDeveloperSettings", L"TaskbarEndTask");

    std::wcout << L"Disabling news\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Dsh", L"AllowNewsAndInterests");

    std::wcout << L"Disabling Windows Copilot\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", L"TurnOffWindowsCopilot");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCopilotButton");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", L"TurnOffWindowsCopilot");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCopilotButton");

    std::wcout << L"Setting taskbar to left as in Windows 10\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarAl");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarAl");

    std::wcout << L"Setting old right-click menus as default in Windows 10\n";
    DeleteRegistryValue(HKEY_CURRENT_USER, L"Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", L"");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", L"");

    std::wcout << L"Disabling Windows Consumer Features\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\PolicyManager\\default\\Experience\\AllowWindowsConsumerFeatures", L"value");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableWindowsTips");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"DoNotShowFeedbackNotifications");
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableWindowsConsumerFeatures");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338388Enabled");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353694Enabled");
    DeleteRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353696Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338388Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353694Enabled");
    DeleteRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353696Enabled");

    std::wcout << L"Disabling telemetry\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"AllowTelemetry");

    std::wcout << L"Disabling advertising ID\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\AdvertisingInfo", L"DisabledByGroupPolicy");

    std::wcout << L"Disabling scheduled tasks related to customer experience and feedback\n";
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Autochk\\Proxy\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\Consolidator\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\UsbCeip\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\DiskDiagnostic\\Microsoft-Windows-DiskDiagnosticDataCollector\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClient\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClientOnScenarioDownload\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Windows Error Reporting\\QueueReporting\" /Disable > nul");

    std::wcout << L"Stopping and disabling Diagnostic Tracking Service\n";
    EnableAndStartService(L"DiagTrack");

    std::wcout << L"Making Windows use UTC time to fix Linux dual boot\n";
    DeleteRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation", L"value");

    std::wcout << L"Finished optimization.\n";
}