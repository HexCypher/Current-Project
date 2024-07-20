// SelfAwareness.h
#ifndef SELFAWARENESS_H
#define SELFAWARENESS_H

#include <windows.h>

class SelfAwareness {
public:
    static byte GetCombatFlag(HANDLE handle, uintptr_t combatFlagAddr);
};

#endif // SELFAWARENESS_H
