// Awareness.h .005

#ifndef AWARENESS_H
#define AWARENESS_H

#include <Windows.h>
#include <iostream>

namespace Awareness {
    // Function to get the target GUID from a given address
    uintptr_t GetTargetGuid(HANDLE handle, uintptr_t targetGuidAddr);

    // Function to get the target GUID and coordinates from the base address
    bool GetTargetInfo(HANDLE handle, DWORD baseAddr, uint32_t& targetGuid, float& x, float& y, float& z);
}

#endif // AWARENESS_H
