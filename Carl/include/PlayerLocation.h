#pragma once

#include <windows.h>

class PlayerLocation {
public:
    static float getX(uintptr_t moduleBase, HANDLE handle);
    static float getY(uintptr_t moduleBase, HANDLE handle);
    static float getZ(uintptr_t moduleBase, HANDLE handle);
    static float getFacing(uintptr_t moduleBase, HANDLE handle);
    static void setFacing(uintptr_t moduleBase, HANDLE handle, float facing);
};

extern float calculateAngle(float x1, float y1, float x2, float y2);
extern bool isFacingTarget(float charX, float charY, float charFacing, float targetX, float targetY);
extern void faceTarget(float charX, float charY, float& charFacing, float targetX, float targetY);
