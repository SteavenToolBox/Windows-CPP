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
        NULL, -1, NULL, NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL, EOAC_NONE, NULL
    );
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize security." << std::endl;
        CoUninitialize();
        return;
    }

    // Obtain the initial locator to WMI.
    IWbemLocator* pLoc = NULL;
    hres = CoCreateInstance(
        CLSID_WbemLocator, 0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator, (LPVOID*)&pLoc
    );
    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object." << std::endl;
        CoUninitialize();
        return;
    }

    IWbemServices* pSvc = NULL;
    hres = pLoc->ConnectServer(
        _bstr_t(L"ROOT\\CIMV2"),
        NULL, NULL, 0, NULL, 0, 0, &pSvc
    );
    if (FAILED(hres)) {
        std::cerr << "Could not connect to WMI namespace." << std::endl;
        pLoc->Release();
        CoUninitialize();
        return;
    }

    hres = CoSetProxyBlanket(
        pSvc,
        RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL,
        RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL, EOAC_NONE
    );
    if (FAILED(hres)) {
        std::cerr << "Could not set proxy blanket." << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // Get logical disks
    IEnumWbemClassObject* pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        bstr_t("WQL"),
        bstr_t("SELECT * FROM Win32_LogicalDisk"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL, &pEnumerator
    );
    if (FAILED(hres)) {
        std::cerr << "Query for logical disks failed." << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    // First pass: Run CHKDSK on all drives
    {
        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (pEnumerator) {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
            if (0 == uReturn) break;

            VARIANT vtProp;
            hr = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);

            std::wstring deviceID = vtProp.bstrVal;
            VariantClear(&vtProp);

            std::wcout << L"Running CHKDSK on " << deviceID << std::endl;
            std::wstring chkdskCommand = L"chkdsk " + deviceID + L" /f";
            runCommand(chkdskCommand);

            pclsObj->Release();
        }

        pEnumerator->Release();
    }

    // Second pass: Run DEFRAG on eligible drives
    {
        // Need to query again
        hres = pSvc->ExecQuery(
            bstr_t("WQL"),
            bstr_t("SELECT * FROM Win32_LogicalDisk"),
            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
            NULL, &pEnumerator
        );
        if (FAILED(hres)) {
            std::cerr << "Query for logical disks failed (second pass)." << std::endl;
            pSvc->Release();
            pLoc->Release();
            CoUninitialize();
            return;
        }

        IWbemClassObject* pclsObj = NULL;
        ULONG uReturn = 0;

        while (pEnumerator) {
            HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
            if (0 == uReturn) break;

            VARIANT vtProp;
            hr = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);

            std::wstring deviceID = vtProp.bstrVal;
            VariantClear(&vtProp);

            // Now fetch associated Disk Model and MediaType
            std::wstring query = L"ASSOCIATORS OF {Win32_LogicalDisk.DeviceID='" + deviceID + L"'} WHERE AssocClass=Win32_LogicalDiskToPartition";
            IEnumWbemClassObject* pPartitionEnum = NULL;
            hres = pSvc->ExecQuery(
                bstr_t("WQL"),
                bstr_t(query.c_str()),
                WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                NULL, &pPartitionEnum
            );

            if (FAILED(hres)) {
                pclsObj->Release();
                continue;
            }

            IWbemClassObject* pPartitionObj = NULL;
            ULONG uPartitionReturn = 0;

            HRESULT hrPartition = pPartitionEnum->Next(WBEM_INFINITE, 1, &pPartitionObj, &uPartitionReturn);
            if (uPartitionReturn) {
                VARIANT vtPartition;
                hrPartition = pPartitionObj->Get(L"DeviceID", 0, &vtPartition, 0, 0);

                std::wstring partitionID = vtPartition.bstrVal;
                VariantClear(&vtPartition);

                std::wstring diskQuery = L"ASSOCIATORS OF {Win32_DiskPartition.DeviceID='" + partitionID + L"'} WHERE AssocClass=Win32_DiskDriveToDiskPartition";
                IEnumWbemClassObject* pDiskEnum = NULL;
                hres = pSvc->ExecQuery(
                    bstr_t("WQL"),
                    bstr_t(diskQuery.c_str()),
                    WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                    NULL, &pDiskEnum
                );

                if (SUCCEEDED(hres)) {
                    IWbemClassObject* pDiskObj = NULL;
                    ULONG uDiskReturn = 0;
                    HRESULT hrDisk = pDiskEnum->Next(WBEM_INFINITE, 1, &pDiskObj, &uDiskReturn);
                    if (uDiskReturn) {
                        VARIANT vtModel, vtMediaType;
                        hrDisk = pDiskObj->Get(L"Model", 0, &vtModel, 0, 0);
                        hrDisk = pDiskObj->Get(L"MediaType", 0, &vtMediaType, 0, 0);

                        std::wstring model = vtModel.bstrVal;
                        std::wstring mediaType = vtMediaType.bstrVal;
                        VariantClear(&vtModel);
                        VariantClear(&vtMediaType);

                        if (model != L"Red Hat VirtIO SCSI Disk Device" && mediaType != L"SSD") {
                            std::wcout << L"Running DEFRAG on " << deviceID << std::endl;
                            std::wstring defragCommand = L"defrag " + deviceID + L"\\ /O";

                            runCommand(defragCommand);
                        }
                        else {
                            std::wcout << L"Skipping DEFRAG on " << deviceID << L" - Disk model: " << model << std::endl;
                        }

                        pDiskObj->Release();
                    }
                    pDiskEnum->Release();
                }
                pPartitionObj->Release();
            }
            pPartitionEnum->Release();
            pclsObj->Release();
        }
        pEnumerator->Release();
    }

    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}
