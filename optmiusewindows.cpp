#include <windows.h>
#include <iostream>
#include <string>
#include "general.h"

void OptmiuseWindows() {
    std::wcout << L"Disabling Web Search and Cortana\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCortana", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCloudSearch", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowCortanaAboveLock", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"ConnectedSearchUseWeb", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"AllowSearchToUseLocation", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"DisableWebSearch", 1);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\Explorer", L"DisableSearchBoxSuggestions", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Policies\\Microsoft\\Windows\\Explorer", L"DisableSearchBoxSuggestions", 1);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Search", L"BingSearchEnabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Search", L"BingSearchEnabled", 0);

    std::wcout << L"Hiding Cortana From Taskbar\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton", 0);

    std::wcout << L"Hiding Teams Icon From Taskbar\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarMn", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarMn", 0);

    std::wcout << L"Disabling Telemetry\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"AllowTelemetry", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"DoNotShowFeedbackNotifications", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\DataCollection", L"AllowTelemetry", 0);

    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Application Experience\\Microsoft Compatibility Appraiser\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Application Experience\\ProgramDataUpdater\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Autochk\\Proxy\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\Consolidator\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\UsbCeip\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\DiskDiagnostic\\Microsoft-Windows-DiskDiagnosticDataCollector\" /Disable>nul");

    std::wcout << L"Disabling Wi-Fi Sense\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\PolicyManager\\default\\Wifi\\AllowAutoConnectToWiFiSenseHotspots", L"value", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\PolicyManager\\default\\Wifi\\AllowWiFiHotSpotReporting", L"value", 0);

    std::wcout << L"Disabling Application suggestions\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"ContentDeliveryAllowed", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"OemPreInstalledAppsEnabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"PreInstalledAppsEnabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"PreInstalledAppsEverEnabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SilentInstalledAppsEnabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338387Enabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338388Enabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353698Enabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338393Enabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353694Enabled", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353696Enabled", 0);

    std::wcout << L"Disabling Activity History\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"EnableActivityFeed", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"PublishUserActivities", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\System", L"UploadUserActivities", 0);

    std::wcout << L"Disabling Location Tracking\n";
    SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\location", L"Value", L"Deny");
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Sensor\\Overrides\\{BFA794E4-F964-4FDB-90F6-51056BFE4B44}", L"SensorPermissionState", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\lfsvc\\Service\\Configuration", L"Status", 0);

    std::wcout << L"Disabling Feedback\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Siuf\\Rules", L"NumberOfSIUFInPeriod", 0);
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClient\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClientOnScenarioDownload\" /Disable>nul");
    StopAndDisableService(L"DiagTrack");
    StopAndDisableService(L"dmwappushservice");

    std::wcout << L"Disabling Advertising ID\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", L"Enabled", 0);

    std::wcout << L"Disabling Error reporting\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\Windows Error Reporting", L"Disabled", 1);
    
    std::wcout << L"Restricting Windows Update P2P only to local network\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DeliveryOptimization\\Config", L"DODownloadMode", 1);

    std::wcout << L"Stopping and disabling Diagnostics Tracking Service\n";
    StopAndDisableService(L"DiagTrack");

    std::wcout << L"Stopping and disabling WAP Push Service\n";
    StopAndDisableService(L"dmwappushservice");

    std::wcout << L"Enabling F8 boot menu options\n";
    ExecuteCommand(L"%SystemRoot%\\System32\\bcdedit.exe /set {current} bootmenupolicy Legacy>nul");

    std::wcout << L"Stopping and disabling Home Groups services\n";
    StopAndDisableService(L"HomeGroupListener");
    StopAndDisableService(L"HomeGroupProvider");

    std::wcout << L"Disabling Remote Assistance\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Remote Assistance", L"fAllowToGetHelp", 0);

    std::wcout << L"Enabling Hibernation\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Power", L"HibernateEnabled", 1);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\FlyoutMenuSettings", L"ShowHibernateOption", 1);

    std::wcout << L"Showing file operations details\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\OperationStatusManager", L"EnthusiastMode", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\OperationStatusManager", L"EnthusiastMode", 1);

    std::wcout << L"Hiding Cortana Button\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCortanaButton", 0);

    std::wcout << L"Hiding Task View button\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowTaskViewButton", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowTaskViewButton", 0);

    std::wcout << L"Hiding People icon\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\People", L"PeopleBand", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\People", L"PeopleBand", 0);

    std::wcout << L"Hide tray icons\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"EnableAutoTray", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"EnableAutoTray", 1);

    std::wcout << L"Enabling NumLock after startup\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Keyboard", L"InitialKeyboardIndicators", 558319670);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Control Panel\\Keyboard", L"InitialKeyboardIndicators", 558319670);
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Keyboard", L"InitialKeyboardIndicators", L"2");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Keyboard", L"InitialKeyboardIndicators", L"2");

    std::wcout << L"Changing default Explorer view to This PC\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"LaunchTo", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"LaunchTo", 1);

    std::wcout << L"Improving System Responsiveness using regedit\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"NetworkThrottlingIndex", 10);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"SystemResponsiveness", 20);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control", L"WaitToKillServiceTimeout", 2000);
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"AutoEndTasks", L"1");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"AutoEndTasks", L"1");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"HungAppTimeout", L"1000");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"HungAppTimeout", L"1000");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"MenuShowDelay", L"1");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"MenuShowDelay", L"1");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"WaitToKillAppTimeout", L"2000");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"WaitToKillAppTimeout", L"2000");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Desktop", L"LowLevelHooksTimeout", L"1000");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Desktop", L"LowLevelHooksTimeout", L"1000");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseHoverTime", L"400");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseHoverTime", L"400");
    SetRegistryString(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control", L"WaitToKillServiceTimeout", L"2000");

    std::wcout << L"Disabling Sync Provider Notifications\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowSyncProviderNotifications", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowSyncProviderNotifications", 0);
    
    std::wcout << L"Disabling Subscribed Content 338387\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338387Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338387Enabled", 0);

    std::wcout << L"Disabling Subscribed Content 338393\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338393Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338393Enabled", 0);
    
    std::wcout << L"Disabling Subscribed Content 310093\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-310093Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-310093Enabled", 0);
    
    std::wcout << L"Disabling Subscribed Content 338389\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled", 0);
    
    std::wcout << L"Disabling Subscribed Content 314563\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-314563Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-314563Enabled", 0);
    
    std::wcout << L"Disabling Soft Landing\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SoftLandingEnabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SoftLandingEnabled", 0);
    
    std::wcout << L"Disabling Scoobe System Setting\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\UserProfileEngagement", L"ScoobeSystemSettingEnabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\UserProfileEngagement", L"ScoobeSystemSettingEnabled", 0);
    
    std::wcout << L"Disabling Silent Installed Apps\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SilentInstalledAppsEnabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SilentInstalledAppsEnabled", 0);
    
    std::wcout << L"Disabling Advertising Info\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", L"Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\AdvertisingInfo", L"Enabled", 0);
    
    std::wcout << L"Disabling Tailored Experiences with Diagnostic Data\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Privacy", L"TailoredExperiencesWithDiagnosticDataEnabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Privacy", L"TailoredExperiencesWithDiagnosticDataEnabled", 0);
    
    std::wcout << L"Enabling Periodic Backup\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Configuration Manager", L"EnablePeriodicBackup", 1);
    
    std::wcout << L"Enabling Expressive Input Shell Hotkey\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Input\\Settings", L"EnableExpressiveInputShellHotkey", 1);

    std::wcout << L"Disabling New App Alert\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Explorer", L"NoNewAppAlert", 1);

    std::wcout << L"Enabling Display Parameters\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\CrashControl", L"DisplayParameters", 1);

    std::wcout << L"Adding Install this update to CABFolder Shell\n";
    SetRegistryString(HKEY_CLASSES_ROOT, L"CABFolder\\Shell\\RunAs", L"", L"Install this update");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CABFolder\\Shell\\RunAs", L"HasLUAShield", L"");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CABFolder\\Shell\\RunAs\\Command", L"", L"cmd /k dism /online /add-package /packagepath:\"%%1\"");

    std::wcout << L"Adding Kill not responding tasks to DesktopBackground Shell\n";
    SetRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"", L"Kill not responding tasks");
    SetRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"icon", L"taskmgr.exe,-30651");
    SetRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"MUIVerb", L"Kill not responding tasks");
    SetRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding", L"Position", L"Top");
    SetRegistryString(HKEY_CLASSES_ROOT, L"DesktopBackground\\Shell\\KillNotResponding\\command", L"", L"cmd.exe /K taskkill.exe /F /FI \"status eq NOT RESPONDING\"");

    std::wcout << L"Adding Personalization to CLSID\n";
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"", L"@%SystemRoot%\\System32\\themecpl.dll,-1#immutable1");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"InfoTip", L"@%SystemRoot%\\System32\\themecpl.dll,-2#immutable1");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"System.ApplicationName", L"Microsoft.Personalization");
    SetRegistryValue(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"System.ControlPanel.Category", 1);
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"System.Software.TasksFileUrl", L"Internal");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}\\DefaultIcon", L"", L"%SystemRoot%\\System32\\themecpl.dll,-1");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}\\Shell\\Open\\command", L"", L"explorer shell:::{ED834ED6-4B5A-4bfe-8F11-A626DCB6A921}");
    SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ControlPanel\\NameSpace\\{580722ff-16a7-44c1-bf74-7e1acd00f4f9}", L"", L"Personalization");
   
    std::wcout << L"Adding Windows Update to CLSID\n";
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"System.Software.TasksFileUrl", L"Internal");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"System.ApplicationName", L"Microsoft.WindowsUpdate");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"System.ControlPanel.Category", L"5");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"", L"@%SystemRoot%\\system32\\shell32.dll,-22068");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"InfoTip", L"@%SystemRoot%\\system32\\shell32.dll,-22580");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}\\DefaultIcon", L"", L"shell32.dll,-47");
    SetRegistryString(HKEY_CLASSES_ROOT, L"CLSID\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}\\Shell\\Open\\Command", L"", L"control.exe /name Microsoft.WindowsUpdate");
    SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ControlPanel\\NameSpace\\{36eef7db-88ad-4e81-ad49-0e313f0c35f8}", L"", L"Windows Update");

    std::wcout << L"Disabling Tailored Experiences with Diagnostic Data for Current User\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableTailoredExperiencesWithDiagnosticData", 1);

    std::wcout << L"Disabling Tailored Experiences with Diagnostic Data for Default User\n";
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableTailoredExperiencesWithDiagnosticData", 1);

    std::wcout << L"Enabling Long Paths\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\FileSystem", L"LongPathsEnabled", 1);
    
    std::wcout << L"Configuring Driver Search Order\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\DriverSearching", L"SearchOrderConfig", 1);

    std::wcout << L"Setting System Responsiveness\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"SystemResponsiveness", 0);

    std::wcout << L"Disabling Network Throttling\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile", L"NetworkThrottlingIndex", 4294967295);

    std::wcout << L"Disabling Clear Page File at Shutdown\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Memory Management", L"ClearPageFileAtShutdown", 0);

    std::wcout << L"Setting NDU Service Start to Automatic\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\ControlSet001\\Services\\Ndu", L"Start", 2);

    std::wcout << L"Setting IRPStackSize\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Services\\LanmanServer\\Parameters", L"IRPStackSize", 30);

    std::wcout << L"Disabling Windows Feeds for Current User\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Policies\\Microsoft\\Windows\\Windows Feeds", L"EnableFeeds", 0);

    std::wcout << L"Setting Shell Feeds Taskbar View Mode for Current User\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Feeds", L"ShellFeedsTaskbarViewMode", 2);

    std::wcout << L"Hiding Meet Now for Current User\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", L"HideSCAMeetNow", 1);

    std::wcout << L"Disabling Windows Feeds for Default User\n";
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\Windows Feeds", L"EnableFeeds", 0);

    std::wcout << L"Setting Shell Feeds Taskbar View Mode for Default User\n";
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Feeds", L"ShellFeedsTaskbarViewMode", 2);

    std::wcout << L"Hiding Meet Now for Default User\n";
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer", L"HideSCAMeetNow", 1);

    std::wcout << L"Setting GPU Priority for Games\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"GPU Priority", 8);

    std::wcout << L"Setting Priority for Games\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"Priority", 6);

    std::wcout << L"Setting Scheduling Category for Games\n";
    SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Multimedia\\SystemProfile\\Tasks\\Games", L"Scheduling Category", L"High");

    std::wcout << L"Disabling sound for Sticky Keys, Toggle Keys, and Filter Keys\n";
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\StickyKeys", L"SOUND", L"");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\StickyKeys", L"SOUND", L"");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\ToggleKeys", L"SOUND", L"");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\ToggleKeys", L"SOUND", L"");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\Keyboard Response", L"SOUND", L"");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\Keyboard Response", L"SOUND", L"");

    std::wcout << L"Disabling warning messages for Sticky Keys, Toggle Keys, and Filter Keys\n";
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\StickyKeys", L"Warning", L"0");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\StickyKeys", L"Warning", L"0");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\ToggleKeys", L"Warning", L"0");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\ToggleKeys", L"Warning", L"0");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Accessibility\\Keyboard Response", L"Warning", L"0");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Accessibility\\Keyboard Response", L"Warning", L"0");

    std::wcout << L"Disabling mouse acceleration\n";
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseSpeed", L"0");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseSpeed", L"0");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold1", L"0");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseThreshold1", L"0");
    SetRegistryString(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseThreshold2", L"0");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseThreshold2", L"0");

    std::wcout << L"Enabling pointer shadow\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Control Panel\\Mouse", L"MouseShadow", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Control Panel\\Mouse", L"MouseShadow", 1);

    std::wcout << L"Disabling showing frequently used folders in Quick Access\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"ShowFrequent", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer", L"ShowFrequent", 0);

    std::wcout << L"Showing hidden files in File Explorer\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"Hidden", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\ware\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"Hidden", 1);

    std::wcout << L"Showing file extensions for unknown file types\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideFileExt", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideFileExt", 0);

    std::wcout << L"Setting Windows Explorer to launch folders in a separate process\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"SeparateProcess", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"SeparateProcess", 1);

    std::wcout << L"Enabling check boxes for file and folder selection in File Explorer\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"CheckFileExtensions", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"CheckFileExtensions", 1);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"AutoCheckSelect", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"AutoCheckSelect", 1);

    std::wcout << L"Showing all folders and libraries in File Explorer\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowAllFolders", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowAllFolders", 1);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowLibraries", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"NavPaneShowLibraries", 1);

    std::wcout << L"Setting indexing options to index the entire C: drive\n";
    SetRegistryString(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Search\\CrawlScopeManager\\Windows\\SystemIndex\\DefaultRules", L"0", L"C:\\");
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows Search\\CrawlScopeManager\\Windows\\SystemIndex\\DefaultRules", L"1", 1);

    std::wcout << L"Tweaking Desktop Icons\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideIcons", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"HideIcons", 0);
    SetRegistryString(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"AutoArrange", L"1");
    SetRegistryString(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"AutoArrange", L"1");
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"FFLAGS", 1075839525);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\Shell\\Bags\\1\\Desktop", L"FFLAGS", 1075839525);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{20D04FE0-3AEA-1069-A2D8-08002B30309D}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{59031a47-3f72-44a7-89c5-5595fe6b30ee}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\NewStartPanel", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\HideDesktopIcons\\ClassicStartMenu", L"{5399E694-6CE5-4D6C-8FCE-1D8870FDCBA0}", 0);

    std::wcout << L"Setting dark mode\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"AppsUseLightTheme", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"AppsUseLightTheme", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"SystemUsesLightTheme", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"SystemUsesLightTheme", 0);

    std::wcout << L"Enabling end task in taskbar\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\TaskbarDeveloperSettings", L"TaskbarEndTask", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced\\TaskbarDeveloperSettings", L"TaskbarEndTask", 1);

    std::wcout << L"Disabling news\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Dsh", L"AllowNewsAndInterests", 0);

    std::wcout << L"Disabling Windows Copilot\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", L"TurnOffWindowsCopilot", 1);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCopilotButton", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Windows\\WindowsCopilot", L"TurnOffWindowsCopilot", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"ShowCopilotButton", 0);

    std::wcout << L"Setting taskbar to left as in Windows 10\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarAl", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", L"TaskbarAl", 0);

    std::wcout << L"Setting old right-click menus as default in Windows 10\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", L"", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Classes\\CLSID\\{86ca1aa0-34aa-4e8b-a509-50c905bae2a2}\\InprocServer32", L"", 0);

    std::wcout << L"Disabling Windows Consumer Features\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\PolicyManager\\default\\Experience\\AllowWindowsConsumerFeatures", L"value", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableWindowsTips", 1);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"DoNotShowFeedbackNotifications", 1);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\CloudContent", L"DisableWindowsConsumerFeatures", 1);
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338388Enabled", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353694Enabled", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353696Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338388Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-338389Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353694Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Microsoft\\Windows\\CurrentVersion\\ContentDeliveryManager", L"SubscribedContent-353696Enabled", 0);

    std::wcout << L"Disabling telemetry\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\DataCollection", L"AllowTelemetry", 0);

    std::wcout << L"Disabling advertising ID\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Policies\\Microsoft\\Windows\\AdvertisingInfo", L"DisabledByGroupPolicy", 1);

    std::wcout << L"Disabling scheduled tasks related to customer experience and feedback\n";
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Autochk\\Proxy\" /Disable>nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\Consolidator\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Customer Experience Improvement Program\\UsbCeip\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\DiskDiagnostic\\Microsoft-Windows-DiskDiagnosticDataCollector\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClient\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Feedback\\Siuf\\DmClientOnScenarioDownload\" /Disable > nul");
    ExecuteCommand(L"schtasks /Change /TN \"Microsoft\\Windows\\Windows Error Reporting\\QueueReporting\" /Disable > nul");

    std::wcout << L"Stopping and disabling Diagnostic Tracking Service\n";
    StopAndDisableService(L"DiagTrack");

    std::wcout << L"Making Windows use UTC time to fix Linux dual boot\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\TimeZoneInformation", L"RealTimeIsUniversal", 1);

    std::wcout << L"Disabling Visual Studio Telemtery\n";
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\VSCommon\\15.0\\SQM", L"OptIn", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\VSCommon\\16.0\\SQM", L"OptIn", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\WOW6432Node\\Microsoft\\VSCommon\\17.0\\SQM", L"OptIn", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\VSCommon\15.0\\SQM", L"OptIn", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\VSCommon\16.0\\SQM", L"OptIn", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\VSCommon\17.0\\SQM", L"OptIn", 0);
    SetRegistryValue(HKEY_LOCAL_MACHINE, L"Software\\Policies\\Microsoft\\VisualStudio\\SQM", L"OptIn", 0);

    std::wcout << L"Disabling Office 365 Telemtery\n";
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common", L"QMEnable", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common", L"UpdateReliabilityData", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Feedback", L"IncludeEmail", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Feedback", L"Enabled", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Feedback", L"SurveyEnabled", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"DisconnectedState", 2);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"UserContentDisabled", 2);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"DownloadContentDisabled", 2);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"ControllerConnectedServicesEnabled", 2);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\osm", L"EnableFileObfuscation", 1);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\16.0\\osm", L"EnableUpload", 0);
    SetRegistryValue(HKEY_CURRENT_USER, L"Software\\Policies\\Microsoft\\Office\\Common\\ClientTelemetry", L"SendTelemetry", 3);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common", L"QMEnable", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common", L"UpdateReliabilityData", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Feedback", L"IncludeEmail", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Feedback", L"Enabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Feedback", L"SurveyEnabled", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"DisconnectedState", 2);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"UserContentDisabled", 2);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"DownloadContentDisabled", 2);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\Common\\Privacy", L"ControllerConnectedServicesEnabled", 2);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\osm", L"EnableFileObfuscation", 1);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\16.0\\osm", L"EnableUpload", 0);
    SetRegistryValue(HKEY_USERS, L".DEFAULT\\Software\\Policies\\Microsoft\\Office\\Common\\ClientTelemetry", L"SendTelemetry", 3);

    std::wcout << L"Finished optimization.\n";
}