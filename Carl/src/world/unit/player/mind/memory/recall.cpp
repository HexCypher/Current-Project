// Recall.cpp
#include "Recall.h"
#include <iostream>
#include <tlhelp32.h>

Recall::Recall(const std::wstring& processName) : processName(processName), hProcess(NULL), procId(0) {
    procId = GetProcId();
    hProcess = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId);
    if (hProcess == NULL) {
        std::cerr << "Failed to open process for reading" << std::endl;
    }
}

Recall::~Recall() {
    if (hProcess != NULL) {
        CloseHandle(hProcess);
    }
}

HANDLE Recall::GetHandle() {
    return hProcess;
}

DWORD Recall::GetProcId() {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry{};
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!_wcsicmp(procEntry.szExeFile, processName.c_str())) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}

uintptr_t Recall::GetModuleBaseAddress(const std::wstring& moduleName) {
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry{};
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!_wcsicmp(modEntry.szModule, moduleName.c_str())) {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

uintptr_t Recall::FindDMAaddress(uintptr_t baseAddr, const std::vector<unsigned int>& offsets) {
    uintptr_t addr = baseAddr;
    for (unsigned int i = 0; i < offsets.size(); ++i) {
        DWORD tempAddr;
        if (!ReadProcessMemory(hProcess, (LPCVOID)addr, &tempAddr, sizeof(tempAddr), nullptr)) {
            DWORD error = GetLastError();
            std::cerr << "Error reading memory at address: " << std::hex << addr
                << std::dec << " (Error Code: " << error << ")" << std::endl;
            if (error == ERROR_NOACCESS) {
                std::cerr << "ERROR_NOACCESS: Invalid access to memory location." << std::endl;
            }
            return 0;
        }
        addr = (uintptr_t)tempAddr + offsets[i];
    }
    return addr;
}

bool Recall::ReadMemory(LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize) {
    SIZE_T bytesRead;
    if (!ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, &bytesRead)) {
        std::cerr << "Failed to read process memory" << std::endl;
        return false;
    }
    return bytesRead == nSize;
}

template<typename T>
T Recall::ReadMemory(LPCVOID lpBaseAddress) {
    T buffer;
    ReadMemory(lpBaseAddress, &buffer, sizeof(T));
    return buffer;
}
