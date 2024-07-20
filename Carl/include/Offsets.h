// Offsets.h
#ifndef OFFSETS_H
#define OFFSETS_H

#include <vector>

namespace Offsets {
    extern const std::vector<unsigned int> combatFlagOffsets;
    const uintptr_t CombatFlag = 0x00C7BCD4; // Example base address, replace with actual base address
    const uintptr_t PlayerX = 0x87B544;
    const uintptr_t PlayerY = 0x87B548;
    const uintptr_t PlayerZ = 0x87B54C;
    // Add other offsets here
}

#endif // OFFSETS_H
