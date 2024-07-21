// Main.cpp
// Version: .005

#include <iostream>
#include <vector>
#include "Permissions.h"
#include "Recall.h"
#include "PlayerLocation.h"
#include "SelfAwareness.h"
#include "Offsets.h"

// Define your entity structure
struct Entity {
    DWORD guid;
    float x, y, z;
    // Additional attributes if any
};

// Function to read and parse the entity list
std::vector<Entity> ParseEntityList(HANDLE hProcess, uintptr_t entityListBaseAddress) {
    std::vector<Entity> entityList;
    uintptr_t currentAddress = entityListBaseAddress;
    const DWORD headerValue = 0x00810810;
    DWORD buffer[1000]; // Adjust the size based on your needs

    // Read a large chunk of memory to find the pattern
    if (!ReadProcessMemory(hProcess, (BYTE*)currentAddress, buffer, sizeof(buffer), nullptr)) {
        std::cerr << "Failed to read entity list data at address: " << std::hex << currentAddress
            << " (Error Code: " << GetLastError() << ")" << std::endl;
        return entityList;
    }

    // Iterate through the buffer to find entities
    for (size_t i = 0; i < sizeof(buffer) / sizeof(DWORD); ++i) {
        if (buffer[i] == headerValue) {
            Entity entity;
            entity.guid = buffer[i + 1]; // Assuming GUID is right after the header
            entity.x = *(float*)&buffer[i + 2];
            entity.y = *(float*)&buffer[i + 3];
            entity.z = *(float*)&buffer[i + 4];
            entityList.push_back(entity);

            // For debugging
            std::cout << "Entity found: GUID=" << entity.guid
                << " Position=(" << entity.x << ", " << entity.y << ", " << entity.z << ")" << std::endl;
        }
    }

    return entityList;
}

uintptr_t ResolveEntityListBaseAddress(HANDLE hProcess, uintptr_t playerBaseAddr) {
    DWORD firstPointerValue;
    if (!ReadProcessMemory(hProcess, (LPCVOID)playerBaseAddr, &firstPointerValue, sizeof(firstPointerValue), nullptr)) {
        std::cerr << "Failed to read first pointer at playerBaseAddr: " << std::hex << playerBaseAddr
            << " (Error Code: " << GetLastError() << ")" << std::endl;
        return 0;
    }

    // Here, `firstPointerValue` should now hold the address containing `00810810`
    return static_cast<uintptr_t>(firstPointerValue);
}

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

    // Example: reading XYZ coordinates
    float x = PlayerLocation::getX(moduleBase, handle);
    float y = PlayerLocation::getY(moduleBase, handle);
    float z = PlayerLocation::getZ(moduleBase, handle);

    std::cout << "Player Coordinates: (" << x << ", " << y << ", " << z << ")" << std::endl;

    // Resolve entity list base address
    uintptr_t entityListBaseAddr = ResolveEntityListBaseAddress(handle, playerBaseAddr);
    if (entityListBaseAddr == 0) {
        std::cerr << "Failed to resolve entity list base address." << std::endl;
        CloseHandle(handle);
        return 1;
    }

    std::cout << "Entity List Base Address: " << std::hex << entityListBaseAddr << std::dec << std::endl;
    std::vector<Entity> entities = ParseEntityList(handle, entityListBaseAddr);

    // Output entities for debugging
    for (const auto& entity : entities) {
        std::cout << "Entity: GUID=" << entity.guid
            << " Position=(" << entity.x << ", " << entity.y << ", " << entity.z << ")" << std::endl;
    }

    // Clean up
    CloseHandle(handle);

    return 0;
}
