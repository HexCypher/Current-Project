#include <iostream>
#include <windows.h>
#include <dinput.h>
#include "feet.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

// Global variables
LPDIRECTINPUT8 dInput = nullptr;
LPDIRECTINPUTDEVICE8 dKeyboard = nullptr;

// Function to send key press using DirectInput
void sendKeyDirectInput(WORD key, bool press) {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;
    input.ki.wVk = key;
    input.ki.dwFlags = press ? 0 : KEYEVENTF_KEYUP;

    SendInput(1, &input, sizeof(INPUT));
}

// Function to hold a key for a specified duration using DirectInput
void holdKeyDirectInput(WORD key, int durationMs) {
    sendKeyDirectInput(key, true);
    Sleep(durationMs);
    sendKeyDirectInput(key, false);
}

// Function to turn the character
void turnCharacter(float currentFacing, float targetFacing) {
    const float threshold = 5.0f; // Allowable angle threshold
    float angleDifference = targetFacing - currentFacing;

    // Normalize the angle difference
    while (angleDifference > 180.0f) angleDifference -= 360.0f;
    while (angleDifference < -180.0f) angleDifference += 360.0f;

    if (fabs(angleDifference) < threshold) {
        return; // Already facing the target
    }

    if (angleDifference > 0) {
        holdKeyDirectInput(VK_RIGHT, 100); // Hold right arrow key for 100 ms
    }
    else {
        holdKeyDirectInput(VK_LEFT, 100); // Hold left arrow key for 100 ms
    }
}
