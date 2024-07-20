// Main.cpp
#include <iostream>
#include "Permissions.h"
#include "Recall.h"
#include "PlayerLocation.h"
#include "SelfAwareness.h"
#include "Offsets.h"

int main() {
    if (!Permissions::EnableDebugPrivilege()) {
        std::cerr << "Failed to enable debug privileges" << std::endl;
        return 1;
    }

    Recall recall(L"WoW.exe");

    HANDLE handle = recall.GetHandle();
    if (handle == NULL) {
        std::cerr << "Failed to open process for reading" << std::endl;
        return 1;
    }

    // Example: reading the combat flag
    byte combatFlag = SelfAwareness::GetCombatFlag(handle, Offsets::CombatFlag);
    std::cout << "Combat Flag: " << static_cast<int>(combatFlag) << std::endl;

    // Example: reading XYZ coordinates
    uintptr_t moduleBase = recall.GetModuleBaseAddress(L"WoW.exe"); // Example base address, replace with actual base address
    float x = PlayerLocation::getX(moduleBase, handle);
    float y = PlayerLocation::getY(moduleBase, handle);
    float z = PlayerLocation::getZ(moduleBase, handle);

    std::cout << "Player Coordinates: (" << x << ", " << y << ", " << z << ")" << std::endl;

    return 0;
}
