// Offsets.h
#ifndef OFFSETS_H
#define OFFSETS_H

// Example offsets, replace with actual values
namespace Offsets {
    const uintptr_t playerBase = 0x00C7BCD4;
    const uintptr_t playerX = 0x87B544;
    const uintptr_t playerY = 0x87B548;
    const uintptr_t playerZ = 0x87B54C;
    std::vector<unsigned int> combatFlag = { 0x88, 0x28, 0x8, 0xBA };
}

#endif // OFFSETS_H