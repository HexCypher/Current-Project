// SelfAwareness.cpp
#include "SelfAwareness.h"
#include <iostream>

byte SelfAwareness::GetCombatFlag(HANDLE handle, uintptr_t combatFlagAddr) {
    byte flag = 0;  // Initialize flag
    SIZE_T bytesRead;
    if (!ReadProcessMemory(handle, (LPCVOID)combatFlagAddr, &flag, sizeof(flag), &bytesRead)) {
        std::cerr << "Error reading memory at address: " << std::hex << combatFlagAddr
            << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
        return 0; // Return 0 or handle the error as appropriate
    }

    if (bytesRead != sizeof(flag)) {
        std::cerr << "Error: Not all bytes read. Expected: " << sizeof(flag) << " Actual: " << bytesRead << std::endl;
        return 0;
    }
    return flag;
}
