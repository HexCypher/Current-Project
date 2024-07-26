// Awareness.cpp .013

#include "Awareness.h"
#include <windows.h>

namespace Awareness {
    // Function to get the full GUID from a given address
    uintptr_t GetTargetGuid(HANDLE handle, uintptr_t targetGuidAddr) {
        uintptr_t fullGuid = 0;  // Initialize full GUID
        SIZE_T bytesRead;

        // Read the GUID from the process memory
        if (!ReadProcessMemory(handle, (LPCVOID)targetGuidAddr, &fullGuid, sizeof(fullGuid), &bytesRead)) {
            std::cerr << "Error reading memory at address: " << std::hex << targetGuidAddr
                << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
            return 0; // Return 0 or handle the error as appropriate
        }

        // Check if the correct number of bytes were read
        if (bytesRead != sizeof(fullGuid)) {
            std::cerr << "Error: Not all bytes read. Expected: " << sizeof(fullGuid) << " Actual: " << bytesRead << std::endl;
            return 0;
        }

        // Extract the relevant part of the GUID (last 4 bytes)
        uintptr_t targetGuid = fullGuid & 0xFFFFFFFF;

        return targetGuid;
    }

    // Function to get the target information (GUID and coordinates)
    bool GetTargetInfo(HANDLE handle, DWORD baseAddr, uint32_t& targetGuid, float& x, float& y, float& z) {
        SIZE_T bytesRead;

        // Read the GUID (only last 4 bytes)
        if (!ReadProcessMemory(handle, (LPCVOID)baseAddr, &targetGuid, sizeof(uint32_t), &bytesRead) || bytesRead != sizeof(uint32_t)) {
            std::cerr << "Error reading target GUID at address: " << std::hex << baseAddr << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
            return false;
        }

        // Skip the next 4 bytes (assumed to be f1300005)
        DWORD coordBaseAddr = baseAddr + 8; // Skip 4 bytes for GUID and 4 bytes for f1300005

        // Read the coordinates
        if (!ReadProcessMemory(handle, (LPCVOID)coordBaseAddr, &x, sizeof(x), &bytesRead) || bytesRead != sizeof(x) ||
            !ReadProcessMemory(handle, (LPCVOID)(coordBaseAddr + 4), &y, sizeof(y), &bytesRead) || bytesRead != sizeof(y) ||
            !ReadProcessMemory(handle, (LPCVOID)(coordBaseAddr + 8), &z, sizeof(z), &bytesRead) || bytesRead != sizeof(z)) {
            std::cerr << "Error reading coordinates at address: " << std::hex << coordBaseAddr << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
            return false;
        }

        return true;
    }
}
