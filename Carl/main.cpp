#include <iostream>
#include <windows.h>
#include "console.h"
#include "feet.h"
#include "botLogic.h"
#include "initialization.h"

extern bool botActive;

int main() {
    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // Register hotkey (Numpad 9)
    if (!RegisterHotKey(nullptr, 1, 0, VK_NUMPAD9)) {
        std::cerr << "Failed to register hotkey" << std::endl;
        return 1;
    }

    // Set console window properties
    setConsoleWindowProperties();

    MSG msg = { 0 };

    // Main loop
    while (true) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_HOTKEY) {
                toggleBotActive();
            }
        }

        if (botActive) {
            botLogic();
        }

        Sleep(100); // Adjust the sleep duration as needed
    }

    // Unregister hotkey before exiting
    UnregisterHotKey(nullptr, 1);

    return 0;
}
