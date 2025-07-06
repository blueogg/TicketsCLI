#include <windows.h>
#include <stdio.h>

typedef LONG NTSTATUS;
#define ProcessBasicInformation 0

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
    BYTE           Reserved1[16];
    PVOID          Reserved2[10];
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB {
    BYTE                          Reserved1[2];
    BYTE                          BeingDebugged;
    BYTE                          Reserved2[1];
    PVOID                         Reserved3[2];
    RTL_USER_PROCESS_PARAMETERS*  ProcessParameters;
    // The full struct is longer, but we don’t need more here
} PEB;

typedef struct _PROCESS_BASIC_INFORMATION {
    PVOID Reserved1;
    PEB*  PebBaseAddress;
    PVOID Reserved2[2];
    ULONG_PTR UniqueProcessId;
    PVOID Reserved3;
} PROCESS_BASIC_INFORMATION;

typedef NTSTATUS (WINAPI *NtQueryInformationProcess_t)(
    HANDLE, ULONG, PVOID, ULONG, PULONG
);

int main() {
    HMODULE ntdll = GetModuleHandleA("ntdll.dll");
    if (!ntdll) {
        printf("Failed to load ntdll.dll\n");
        return 1;
    }

    NtQueryInformationProcess_t NtQueryInformationProcess =
        (NtQueryInformationProcess_t)GetProcAddress(ntdll, "NtQueryInformationProcess");

    if (!NtQueryInformationProcess) {
        printf("Failed to get NtQueryInformationProcess\n");
        return 1;
    }

    PROCESS_BASIC_INFORMATION pbi;
    NTSTATUS status = NtQueryInformationProcess(
        GetCurrentProcess(),
        ProcessBasicInformation,
        &pbi,
        sizeof(pbi),
        NULL
    );

    if (status != 0) {
        printf("NtQueryInformationProcess failed with status 0x%X\n", status);
        return 1;
    }

    PEB* peb = pbi.PebBaseAddress;
    RTL_USER_PROCESS_PARAMETERS* params = peb->ProcessParameters;

    WCHAR* original = params->ImagePathName.Buffer;
    wprintf(L"Original: %s\n", original);

    //  Must not overflow the buffer!
    wcscpy_s(original, params->ImagePathName.Length / sizeof(WCHAR), "C:\\Fake\\Spoofed.exe");
    wprintf("Modified: %s\n", params->ImagePathName.Buffer);

    Sleep(60000); // Stay alive to inspect process in Task Manager/Process Hacker

    return 0;
}
