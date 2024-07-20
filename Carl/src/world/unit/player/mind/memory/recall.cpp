// Recall.cpp
#include "Recall.h"
#include <iostream>
#include <tlhelp32.h>

HANDLE Recall::GetHandle(const wchar_t* procName) {
    DWORD procId = GetProcId(procName);
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    return hProcess;
}

DWORD Recall::GetProcId(const wchar_t* procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry{};
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_wcsicmp(procEntry.szExeFile, procName)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

uintptr_t Recall::GetModuleBaseAddress(DWORD procId, const wchar_t* procName) {
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry{};
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, procName)) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t Recall::FindDMAaddress(HANDLE hProc, uintptr_t baseAddr, const std::vector<unsigned int>& offsets) {
    uintptr_t addr = baseAddr;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        DWORD tempAddr;  // Using DWORD to read 4 bytes as Cheat Engine does
        if (!ReadProcessMemory(hProc, (LPCVOID)addr, &tempAddr, sizeof(tempAddr), nullptr)) {
            DWORD error = GetLastError();
            std::cerr << "Error reading memory at address: " << std::hex << addr
                << std::dec << " (Error Code: " << error << ")" << std::endl;
            if (error == ERROR_NOACCESS) {
                std::cerr << "ERROR_NOACCESS: Invalid access to memory location." << std::endl;
            }
            return 0; // Return 0 or handle the error as appropriate
        }
        addr = (uintptr_t)tempAddr + offsets[i];
    }
    return addr;
}
