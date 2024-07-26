// main.cpp .010

#include <iostream>
#include "Permissions.h"
#include "Recall.h"
#include "PlayerLocation.h"
#include "Awareness.h"
#include "SelfAwareness.h"
#include "Offsets.h"

int main() {
    const wchar_t* procName = L"WoW.exe";
    DWORD procID;
    HANDLE handle;
    uintptr_t moduleBase;
    uintptr_t combatFlagAddr;
    byte combatFlag;

    // Enable debug privileges for the process
    if (!Permissions::EnableDebugPrivilege()) {
        std::cerr << "Failed to enable debug privileges" << std::endl;
        return 1;
    }

    // Get the process ID and handle
    procID = Recall::GetProcId(procName);
    handle = Recall::GetHandle(procName);
    moduleBase = Recall::GetModuleBaseAddress(procID, procName);

    // Find the combat flag address
    combatFlagAddr = Recall::FindDMAaddress(handle, Offsets::playerBaseAddr, Offsets::combatFlagOffsets);
    if (combatFlagAddr != 0) {
        uintptr_t finalValue;
        if (ReadProcessMemory(handle, (LPCVOID)combatFlagAddr, &finalValue, sizeof(finalValue), nullptr)) {
            // std::cout << "Final address: " << std::hex << combatFlagAddr << " Value at final address: " << std::hex << finalValue << " InfoPanel->combatFlagAddr" << std::endl;
        }
        else {
            std::cerr << "Failed to read value at final address (Error Code: " << GetLastError() << ")" << std::endl;
        }
    }
    else {
        std::cerr << "Failed to find final address." << std::endl;
    }

    // Get the combat flag
    combatFlag = SelfAwareness::GetCombatFlag(handle, combatFlagAddr);
    std::cout << "Combat Flag: " << static_cast<int>(combatFlag) << std::endl;

    // Read player XYZ coordinates
    float x = PlayerLocation::getX(moduleBase, handle);
    float y = PlayerLocation::getY(moduleBase, handle);
    float z = PlayerLocation::getZ(moduleBase, handle);
    std::cout << "Player Coordinates: (" << x << ", " << y << ", " << z << ")" << std::endl;

    // Use pointer path to get the target information
    uintptr_t baseAddr = moduleBase + 0x0074B2BC; // Base address from module base
    DWORD firstPointerAddr = 0;

    // Resolve the first pointer
    if (!ReadProcessMemory(handle, (LPCVOID)baseAddr, &firstPointerAddr, sizeof(DWORD), nullptr)) {
        std::cerr << "Failed to read first pointer at base address: " << std::hex << baseAddr << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
        CloseHandle(handle);
        return 1;
    }

    // Calculate the target info base address
    DWORD targetInfoBaseAddr = firstPointerAddr + 0x358; // Add the offset

    // Variables to store target information
    uint32_t targetGuid;
    float targetX, targetY, targetZ;

    // Get the target information
    if (Awareness::GetTargetInfo(handle, targetInfoBaseAddr, targetGuid, targetX, targetY, targetZ)) {
        std::cout << "Target GUID: " << std::hex << targetGuid << std::dec << std::endl;
        std::cout << "Target Coordinates: (" << targetX << ", " << targetY << ", " << targetZ << ")" << std::endl;
    }
    else {
        std::cout << "Failed to get target information." << std::endl;
    }

    // Clean up
    CloseHandle(handle);

    return 0;
}
