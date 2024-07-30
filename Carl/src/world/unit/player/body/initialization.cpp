#include <iostream>
#include <windows.h>
#include "feet.h"
#include "console.h"

// Function to initialize DirectInput
bool initializeDirectInput(HINSTANCE hInstance) {
    HRESULT hr;
    hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dInput, nullptr);
    if (FAILED(hr)) {
        std::cerr << "DirectInput8Create failed with error: " << hr << std::endl;
        return false;
    }
    hr = dInput->CreateDevice(GUID_SysKeyboard, &dKeyboard, nullptr);
    if (FAILED(hr)) {
        std::cerr << "CreateDevice failed with error: " << hr << std::endl;
        return false;
    }
    hr = dKeyboard->SetDataFormat(&c_dfDIKeyboard);
    if (FAILED(hr)) {
        std::cerr << "SetDataFormat failed with error: " << hr << std::endl;
        return false;
    }
    hr = dKeyboard->SetCooperativeLevel(GetConsoleWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
    if (FAILED(hr)) {
        std::cerr << "SetCooperativeLevel failed with error: " << hr << std::endl;
        return false;
    }
    return true;
}

// Function to set the console window always on top and resize it
void setConsoleWindowProperties() {
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, HWND_TOPMOST, 0, 0, 500, 600, SWP_NOMOVE | SWP_NOSIZE); // Always on top
    MoveWindow(consoleWindow, 0, 5, 500, 600, TRUE); // Resize and position console
}
