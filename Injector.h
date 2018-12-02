
#ifndef CREATEREMOTETHREAD_INJECTOR_H
#define CREATEREMOTETHREAD_INJECTOR_H

#include <windows.h>
#include "AllicationInfo.h"

#pragma pack(push, 8)

#include <tlhelp32.h>

#pragma pack(pop)

class Injector {
private:
    HANDLE hProcess;

public:
    DWORD processId;

    static Injector *FromWindowByTitle(LPCWSTR title);

    static Injector *FromWindowByClass(LPCWSTR className);

    static Injector *FromExecName(LPCSTR execName);

    static Injector *Run(LPCWSTR execPath);

    Injector(DWORD pid);

    Injector *Open();

    Injector *Open(DWORD flags);

    Injector *Close();

    AllocationInfo *Alloc(SIZE_T Size);

    SIZE_T *Write(AllocationInfo *mem, void *data, SIZE_T *bytesWritten);

    SIZE_T *Read(AllocationInfo *mem, void *data, SIZE_T *bytesToRead);

    Injector *Free(AllocationInfo *info);

    Injector *InjectDLL(wchar_t *dllPath);

    Injector *InjectAsm(AllocationInfo *mem, BYTE *data);
};

#endif //CREATEREMOTETHREAD_INJECTOR_H
