// PlayerLocation.h
#ifndef PLAYERLOCATION_H
#define PLAYERLOCATION_H

#include <windows.h>

class PlayerLocation {
public:
    static float getX(uintptr_t moduleBase, HANDLE handle);
    static float getY(uintptr_t moduleBase, HANDLE handle);
    static float getZ(uintptr_t moduleBase, HANDLE handle);
};

#endif // PLAYERLOCATION_H
