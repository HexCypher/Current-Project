// PlayerLocation.cpp
#include "PlayerLocation.h"
#include "Offsets.h"
#include <iostream>

float PlayerLocation::getX(uintptr_t moduleBase, HANDLE handle) {
    float x = 0.0f;
    uintptr_t xBaseAddr = moduleBase + Offsets::PlayerX;
    ReadProcessMemory(handle, (BYTE*)xBaseAddr, &x, sizeof(x), nullptr);
    return x;
}

float PlayerLocation::getY(uintptr_t moduleBase, HANDLE handle) {
    float y = 0.0f;
    uintptr_t yBaseAddr = moduleBase + Offsets::PlayerY;
    ReadProcessMemory(handle, (BYTE*)yBaseAddr, &y, sizeof(y), nullptr);
    return y;
}

float PlayerLocation::getZ(uintptr_t moduleBase, HANDLE handle) {
    float z = 0.0f;
    uintptr_t zBaseAddr = moduleBase + Offsets::PlayerZ;
    ReadProcessMemory(handle, (BYTE*)zBaseAddr, &z, sizeof(z), nullptr);
    return z;
}
