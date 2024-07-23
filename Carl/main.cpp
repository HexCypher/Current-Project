// Main.cpp
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

    uintptr_t playerBaseAddr = 0x00C7BCD4;

    if (!Permissions::EnableDebugPrivilege()) {
        std::cerr << "Failed to enable debug privileges" << std::endl;
        return 1;
    }

    procID = Recall::GetProcId(procName);
    handle = Recall::GetHandle(procName);
    moduleBase = Recall::GetModuleBaseAddress(procID, procName);

    combatFlagAddr = Recall::FindDMAaddress(handle, playerBaseAddr, Offsets::combatFlagOffsets);
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

    combatFlag = SelfAwareness::GetCombatFlag(handle, combatFlagAddr);
    std::cout << "Combat Flag: " << static_cast<int>(combatFlag) << std::endl;

    // Reading player XYZ coordinates
    float x = PlayerLocation::getX(moduleBase, handle);
    float y = PlayerLocation::getY(moduleBase, handle);
    float z = PlayerLocation::getZ(moduleBase, handle);

    std::cout << "Player Coordinates: (" << x << ", " << y << ", " << z << ")" << std::endl;

    // Reading target guid
    uintptr_t targetGuid = Awareness::GetTargetGuid(handle, Offsets::currentTarget);

    std::cout << "Target GUID: " << std::hex << targetGuid << std::endl;


    // Clean up
    CloseHandle(handle);

    return 0;
}
