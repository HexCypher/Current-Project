// Recall.cpp
#include "Recall.h"
#include <iostream>

Recall::Recall(DWORD pid) {
    hProcess = OpenProcess(PROCESS_VM_READ, FALSE, pid);
    if (hProcess == NULL) {
        std::cerr << "Failed to open process for reading" << std::endl;
    }
}

Recall::~Recall() {
    if (hProcess != NULL) {
        CloseHandle(hProcess);
    }
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
