#include <iostream>
#include <windows.h>
#include "Permissions.h"
#include "Recall.h"
#include "PlayerLocation.h"
#include "Awareness.h"
#include "SelfAwareness.h"
#include "Offsets.h"
#include "console.h"
#include "feet.h"

extern bool botActive;

void botLogic() {
    const wchar_t* procName = L"WoW.exe";
    DWORD procID;
    HANDLE handle;
    uintptr_t moduleBase;
    uintptr_t combatFlagAddr;
    byte combatFlag;

    procID = Recall::GetProcId(procName);
    handle = Recall::GetHandle(procName);
    moduleBase = Recall::GetModuleBaseAddress(procID, procName);

    combatFlagAddr = Recall::FindDMAaddress(handle, Offsets::playerBaseAddr, Offsets::combatFlagOffsets);
    if (combatFlagAddr != 0) {
        uintptr_t finalValue;
        if (ReadProcessMemory(handle, (LPCVOID)combatFlagAddr, &finalValue, sizeof(finalValue), nullptr)) {
            // Successfully read
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

    float charX = PlayerLocation::getX(moduleBase, handle);
    float charY = PlayerLocation::getY(moduleBase, handle);
    float charZ = PlayerLocation::getZ(moduleBase, handle);
    std::cout << "Player Coordinates: (" << charX << ", " << charY << ", " << charZ << ")" << std::endl;

    uintptr_t baseAddr = moduleBase + 0x0074B2BC;
    DWORD firstPointerAddr = 0;

    if (!ReadProcessMemory(handle, (LPCVOID)baseAddr, &firstPointerAddr, sizeof(DWORD), nullptr)) {
        std::cerr << "Failed to read first pointer at base address: " << std::hex << baseAddr << std::dec << " (Error Code: " << GetLastError() << ")" << std::endl;
        CloseHandle(handle);
        return;
    }

    DWORD targetInfoBaseAddr = firstPointerAddr + 0x358;

    uint32_t targetGuid;
    float targetX, targetY, targetZ;

    if (Awareness::GetTargetInfo(handle, targetInfoBaseAddr, targetGuid, targetX, targetY, targetZ)) {
        std::cout << "Target GUID: " << std::hex << targetGuid << std::dec << std::endl;
        std::cout << "Target Coordinates: (" << targetX << ", " << targetY << ", " << targetZ << ")" << std::endl;

        float charFacing = PlayerLocation::getFacing(moduleBase, handle);
        float targetFacing = calculateAngle(charX, charY, targetX, targetY);

        if (!isFacingTarget(charX, charY, charFacing, targetX, targetY)) {
            turnCharacter(charFacing, targetFacing);
        }
        else {
            std::cout << "Facing target" << std::endl;
        }
    }
    else {
        std::cout << "Failed to get target information." << std::endl;
    }

    CloseHandle(handle);
}
