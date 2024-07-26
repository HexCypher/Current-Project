// Offsets.h .003

#ifndef OFFSETS_H
#define OFFSETS_H

#include <vector>

namespace Offsets {
    extern const std::vector<unsigned int> combatFlagOffsets;
    const uintptr_t CombatFlag = 0x00C7BCD4;
    const uintptr_t currentTarget = 0x00B4E2D8;
    const uintptr_t PlayerX = 0x87B544;
    const uintptr_t PlayerY = 0x87B548;
    const uintptr_t PlayerZ = 0x87B54C;
    const uintptr_t playerBaseAddr = 0x00C7BCD4; // Added playerBaseAddr
    // Add other offsets here
}

#endif // OFFSETS_H
