//
// Created by Serabass on 28.11.2018.
//

#include "Injector.h"
#include <iostream>
#include <tchar.h>

void printError(TCHAR *msg) {
    DWORD eNum;
    TCHAR sysMsg[256];
    TCHAR *p;

    eNum = GetLastError();
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL, eNum,
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                  sysMsg, 256, NULL);

    // Trim the end of the line and terminate it with a null
    p = sysMsg;
    while ((*p > 31) || (*p == 9))
        ++p;
    do { *p-- = 0; }
    while ((p >= sysMsg) &&
           ((*p == '.') || (*p < 33)));

    // Display the message
    _tprintf(TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg);
}

Injector::Injector(DWORD pid) {
    processId = pid;
}

Injector *Injector::FromExecName(LPCSTR execName) {
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32 = {0};
    DWORD processId = -1;

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return nullptr;

    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32)) {
        // printError("Process32FirstW");
        CloseHandle(hProcessSnap);
        return nullptr;
    }

    do {
        if (!lstrcmp(execName, pe32.szExeFile)) {
            processId = pe32.th32ProcessID;
            CloseHandle(hProcessSnap);
            return new Injector(processId);
        }
    } while (Process32Next(hProcessSnap, &pe32));

    printf("Process not found");
    throw "Process not found";
}

Injector *Injector::FromWindowByTitle(LPCWSTR title) {
    auto hWnd = FindWindowW(nullptr, title);

    if (!hWnd) {
        printf("Window not found");
        throw L"Window not found";
    }

    DWORD processId;
    GetWindowThreadProcessId(hWnd, &processId);

    return new Injector(processId);
}

Injector *Injector::FromWindowByClass(LPCWSTR className) {
    auto hWnd = FindWindowW(className, nullptr);

    if (!hWnd) {
        printf("Window not found");
        throw L"Window not found";
    }
    DWORD processId;
    GetWindowThreadProcessId(hWnd, &processId);

    return new Injector(processId);
}

Injector *Injector::Run(LPCWSTR execPath) {
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(execPath, nullptr, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi)) {
        printf("Could not spawn process");
        throw L"Could not spawn process";
    }

    return new Injector(pi.dwProcessId);
}

Injector *Injector::Open(DWORD flags) {
    hProcess = OpenProcess(flags, false, processId);
    return this;
}

Injector *Injector::Open() {
    return Open(PROCESS_ALL_ACCESS);
}

// TODO Implement Protection Method
AllocationInfo *Injector::Alloc(SIZE_T size) {
    LPVOID BaseAddress;
    auto pInfo = new AllocationInfo();
    auto baseAddress = (LPVOID) VirtualAllocEx(hProcess, nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    auto x = ERROR_INVALID_ADDRESS;

    if (!baseAddress) {
        printf("VirtualAllocEx");
        throw ("VirtualAllocEx");
    }

    pInfo->AllocatedBaseAddress = baseAddress;
    pInfo->AllocatedSize = size;
    return pInfo;
}

Injector *Injector::Free(AllocationInfo *info) {
    if (!VirtualFreeEx(hProcess, info->AllocatedBaseAddress, 0, MEM_RELEASE)) {
        auto e = GetLastError();
        printf("VirtualFreeEx: %d\n", e);
        // throw "123213";
    }
    return this;
}

SIZE_T *Injector::Write(AllocationInfo *mem, void *data, SIZE_T *bytesWritten) {
    if (0 == WriteProcessMemory(hProcess, mem->AllocatedBaseAddress, data, mem->AllocatedSize, bytesWritten)) {
        printf("Could not WriteProcessMemory");
        throw L"Could not WriteProcessMemory";
    }
    return bytesWritten;
}

SIZE_T *Injector::Read(AllocationInfo *mem, void *data, SIZE_T *bytesWritten) {
    if (0 == ReadProcessMemory(hProcess, mem->AllocatedBaseAddress, data, mem->AllocatedSize, bytesWritten)) {
        printf("Could not ReadProcessMemory");
        throw L"Could not ReadProcessMemory";
    }
    return bytesWritten;
}

Injector *Injector::InjectDLL(wchar_t *dllPath) {
    SIZE_T dllNameLength = (wcslen(dllPath) + 1) * sizeof(WCHAR);
    SIZE_T bytesWritten;
    AllocationInfo *mem = Alloc(dllNameLength);

    try {
        Write(mem, (LPVOID) dllPath, &bytesWritten);
    } catch (EXCEPINFO e) {
        printf("WriteProcessMemory error");
        std::cout << "WriteProcessMemory error\n";
        Free(mem);
        Close();
        LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                      nullptr, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                      (LPTSTR) &lpMsgBuf, 0, nullptr);
        printf("1231312312312312");
        throw "1231312312312312";
    }

    DWORD threadID;
    auto ldrLibW = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryW");
    HANDLE remoteThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE) ldrLibW,
                                             mem->AllocatedBaseAddress, 0, &threadID);

    if (remoteThread == NULL) {
        auto err = GetLastError();
        printf("CreateRemoteThread");
        printError((char *) "CreateRemoteThread");
    }

    if (remoteThread != INVALID_HANDLE_VALUE)
        WaitForSingleObject(remoteThread, INFINITE);

    Free(mem);

    return this;
}

Injector *Injector::InjectAsm(AllocationInfo *mem, BYTE *data) {
    SIZE_T bytesWritten;
    Write(mem, data, &bytesWritten);
    /*
     WriteProcessMemory(hProcess, mem->AllocatedBaseAddress, x, mem->AllocatedSize, bytesWritten);
     Write(mem, &x, &bytesWritten);
     ;
     */
    DWORD threadID;
    HANDLE remoteThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE) mem->AllocatedBaseAddress,
                                             mem->AllocatedBaseAddress, 0, &threadID);

    if (remoteThread == nullptr) {
        auto err = GetLastError();
        printf("CreateRemoteThread");
        printError((char *) "CreateRemoteThread");
    }

    if (remoteThread != INVALID_HANDLE_VALUE)
        WaitForSingleObject(remoteThread, INFINITE);

    return this;
}

#define COUNT 12

Injector *Injector::InjectAsmSandbox() {
    BYTE x[12] = {
            0xB8, 0xC8, 0xAD, 0x94, 0x00,       // mov     eax, 94ADC8h
            0xC7, 0x00, 0xE8, 0x08, 0x00, 0x00, // mov dword ptr [eax], 3E8h
            0xC3                                // retn
    };
    int spawnVehicleFn = 0x4AE8F0;
    AllocationInfo *mem = Alloc(COUNT);
    BYTE instr[4] = {0x00, 0x00, 0x00, 0x00};
    int instruction = -(((unsigned int) mem->AllocatedBaseAddress + 5) - spawnVehicleFn) - 5;
    memcpy(&instr[0], &instruction, 4);
    BYTE spawnVehicle[COUNT] = {
            0x68, 0xCE, 0x00, 0x00, 0x00,                    // push 04
            0xE8, instr[0], instr[1], instr[2], instr[3],  // call FN
            0x59,                                          // pop ecx
            0xC3                                           // ret
    };
    BYTE setWeather[12] = {
            0x68, 0xAC, 0x00, 0x00, 0x00,                   // push 04
            0xE8, instr[0], instr[1], instr[2], instr[3],   // call FN
            // 0xB4, 0x4C,                                  // mov ah,0x4c
            0xC3                                            // ret
    };
    SIZE_T bytesWritten;
    Write(mem, &spawnVehicle, &bytesWritten);
    /*
     WriteProcessMemory(hProcess, mem->AllocatedBaseAddress, x, mem->AllocatedSize, bytesWritten);
     Write(mem, &x, &bytesWritten);
     ;
     */
    DWORD threadID;
    HANDLE remoteThread = CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE) mem->AllocatedBaseAddress,
                                             mem->AllocatedBaseAddress, 0, &threadID);

    if (remoteThread == nullptr) {
        auto err = GetLastError();
        printf("CreateRemoteThread");
        printError((char *) "CreateRemoteThread");
    }

    if (remoteThread != INVALID_HANDLE_VALUE)
        WaitForSingleObject(remoteThread, 1000);

    return this;

}

Injector *Injector::Close() {
    CloseHandle(hProcess);
    return this;
}
