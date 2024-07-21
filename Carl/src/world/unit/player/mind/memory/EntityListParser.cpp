// EntityListParser.cpp
// Version: .002

#include "EntityListParser.h"
#include <iostream>

std::vector<Entity> EntityListParser::ParseEntityList(HANDLE hProcess, uintptr_t entityListBaseAddress) {
    std::vector<Entity> entityList;
    uintptr_t currentAddress = entityListBaseAddress;
    const DWORD headerValue = 0x00810810;
    DWORD buffer[1000]; // Adjust the size based on your needs

    // Read a large chunk of memory to find the pattern
    if (!ReadProcessMemory(hProcess, (BYTE*)currentAddress, buffer, sizeof(buffer), nullptr)) {
        std::cerr << "Failed to read entity list data" << std::endl;
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
