#include <iostream>
#include <comdef.h>
#include <Wbemidl.h>
#include <vector>
#include <string>

#pragma comment(lib, "wbemuuid.lib")

void runCommand(const std::wstring& command) {
    _wsystem(command.c_str());
}

void RepairDrives() {
    HRESULT hres;

    // Initialize COM.
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library." << std::endl;
        return;
    }

    // Initialize security.
    hres = CoInitializeSecurity(
        NULL,
        -1,                          // COM authentication
        NULL,                        // Authentication services
        NULL,                        // Reserved
        RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
        RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation
        NULL,                        // Authentication info
        EOAC_NONE,                   // Additional capabilities 
        NULL                         // Reserved
    );

    if (FAILED(hres)) {
        std::cerr << "Failed to initialize security." << std::endl;
        CoUninitialize();
        return;
    }

    // Obtain the initial locator to WMI.
    IWbemLocator* pLoc = NULL;

    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc);

    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object." << std::endl;
        CoUninitialize();
        return;
    }

    IWbemServices* pSvc = NULL;

    // Connect to the root\cimv2 namespace with the current user.
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL,  // User name
        NULL,  // User password
        0,     // Locale
        NULL,  // Security flags
        0,     // Authority
        0,     // Context object
        &pSvc  // IWbemServices proxy
    );

    if (FAILED(hres)) {
        std::cerr << "Could not connect to WMI namespace." << std::endl;
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // Set security levels on the proxy.
    hres = CoSetProxyBlanket(
        pSvc,                        // Indicates the proxy to set
        RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx 
        RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx 
        NULL,                        // Server principal name 
        RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
        RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
        NULL,                        // client identity
        EOAC_NONE                    // proxy capabilities 
    );

    if (FAILED(hres)) {
        std::cerr << "Could not set proxy blanket." << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // Get logical disks.
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_LogicalDisk"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        std::cerr << "Query for logical disks failed." << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    IWbemClassObject* pclsObj = NULL;
    ULONG uReturn = 0;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;
        hr = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);

        std::wstring deviceID = vtProp.bstrVal;
        VariantClear(&vtProp);

        std::wstring query = L"ASSOCIATORS OF {Win32_LogicalDisk.DeviceID='" + deviceID + L"'} WHERE AssocClass=Win32_LogicalDiskToPartition";
        IEnumWbemClassObject* pPartitionEnum = NULL;
        hr = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t(query.c_str()),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL,
            &pPartitionEnum);

        if (FAILED(hr)) {
            std::cerr << "Query for partitions failed." << std::endl;
            continue;
        }

        IWbemClassObject* pPartitionObj = NULL;
        ULONG uPartitionReturn = 0;

        while (pPartitionEnum) {
            HRESULT hrPartition = pPartitionEnum->Next(WBEM_INFINITE, 1, &pPartitionObj, &uPartitionReturn);

            if (0 == uPartitionReturn) {
                break;
            }

            VARIANT vtPartition;
            hrPartition = pPartitionObj->Get(L"DeviceID", 0, &vtPartition, 0, 0);

            std::wstring partitionID = vtPartition.bstrVal;
            VariantClear(&vtPartition);

            std::wstring diskQuery = L"ASSOCIATORS OF {Win32_DiskPartition.DeviceID='" + partitionID + L"'} WHERE AssocClass=Win32_DiskDriveToDiskPartition";
            IEnumWbemClassObject* pDiskEnum = NULL;
            hrPartition = pSvc->ExecQuery(
                bstr_t("WQL"),
                bstr_t(diskQuery.c_str()),
                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                NULL,
                &pDiskEnum);

            if (FAILED(hrPartition)) {
                std::cerr << "Query for disks failed." << std::endl;
                continue;
            }

            IWbemClassObject* pDiskObj = NULL;
            ULONG uDiskReturn = 0;

            while (pDiskEnum) {
                HRESULT hrDisk = pDiskEnum->Next(WBEM_INFINITE, 1, &pDiskObj, &uDiskReturn);

                if (0 == uDiskReturn) {
                    break;
                }

                VARIANT vtModel, vtMediaType;
                hrDisk = pDiskObj->Get(L"Model", 0, &vtModel, 0, 0);
                hrDisk = pDiskObj->Get(L"MediaType", 0, &vtMediaType, 0, 0);

                std::wstring model = vtModel.bstrVal;
                std::wstring mediaType = vtMediaType.bstrVal;
                VariantClear(&vtModel);
                VariantClear(&vtMediaType);

                if (model != L"Red Hat VirtIO SCSI Disk Device" && mediaType != L"SSD") {
                    std::wstring driveLetter = deviceID;
                    std::wcout << L"Running maintenance on drive " << driveLetter << std::endl;

                    std::wstring chkdskCommand = L"chkdsk " + driveLetter + L" /f";
                    std::wstring defragCommandL = L"defrag " + driveLetter + L"\\ /L";
                    std::wstring defragCommandO = L"defrag " + driveLetter + L"\\ /O";

                    runCommand(chkdskCommand);
                    runCommand(defragCommandL);
                    runCommand(defragCommandO);
                }
                else {
                    std::wcout << L"Skipping drive " << deviceID << L" - Disk model: " << model << std::endl;
                }

                pDiskObj->Release();
            }

            pDiskEnum->Release();
            pPartitionObj->Release();
        }

        pPartitionEnum->Release();
        pclsObj->Release();
    }

    pSvc->Release();
    pLoc->Release();
    pEnumerator->Release();
    CoUninitialize();
}