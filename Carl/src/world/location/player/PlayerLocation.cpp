#include "PlayerLocation.h"
#include "Offsets.h"
#include <cmath>
#include <windows.h>

// Assuming ReadProcessMemory function and necessary offsets are available

float PlayerLocation::getX(uintptr_t moduleBase, HANDLE handle) {
    float x;
    ReadProcessMemory(handle, (LPCVOID)(moduleBase + Offsets::PlayerX), &x, sizeof(x), nullptr);
    return x;
}

float PlayerLocation::getY(uintptr_t moduleBase, HANDLE handle) {
    float y;
    ReadProcessMemory(handle, (LPCVOID)(moduleBase + Offsets::PlayerY), &y, sizeof(y), nullptr);
    return y;
}

float PlayerLocation::getZ(uintptr_t moduleBase, HANDLE handle) {
    float z;
    ReadProcessMemory(handle, (LPCVOID)(moduleBase + Offsets::PlayerZ), &z, sizeof(z), nullptr);
    return z;
}

float PlayerLocation::getFacing(uintptr_t moduleBase, HANDLE handle) {
    float facing;
    ReadProcessMemory(handle, (LPCVOID)(moduleBase + Offsets::facingOffset), &facing, sizeof(facing), nullptr);
    return facing;
}

void PlayerLocation::setFacing(uintptr_t moduleBase, HANDLE handle, float facing) {
    WriteProcessMemory(handle, (LPVOID)(moduleBase + Offsets::facingOffset), &facing, sizeof(facing), nullptr);
}

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

float calculateAngle(float x1, float y1, float x2, float y2) {
    return static_cast<float>(atan2(y2 - y1, x2 - x1) * 180 / M_PI);
}

bool isFacingTarget(float charX, float charY, float charFacing, float targetX, float targetY) {
    float angleToTarget = calculateAngle(charX, charY, targetX, targetY);
    float diff = fmod(fabs(charFacing - angleToTarget), 360.0);
    return (diff < 45.0) || (diff > 315.0);
}

void faceTarget(float charX, float charY, float& charFacing, float targetX, float targetY) {
    charFacing = calculateAngle(charX, charY, targetX, targetY);
}
