// Awareness.cpp .001

#include "Awareness.h"

namespace Awareness {
    uintptr_t GetTargetGuid(HANDLE handle, uintptr_t targetGuidAddr) {
        uintptr_t guid = 0;  // Initialize guid
        SIZE_T bytesRead;

        if (!ReadProcessMemory(handle, (LPCVOID)targetGuidAddr, &guid, sizeof(guid), &bytesRead)) {
            std::cerr << "Error reading memory at address: " << std::hex << targetGuidAddr
                << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
            return 0; // Return 0 or handle the error as appropriate
        }

        if (bytesRead != sizeof(guid)) {
            std::cerr << "Error: Not all bytes read. Expected: " << sizeof(guid) << " Actual: " << bytesRead << std::endl;
            return 0;
        }

        return guid;
    }
}
