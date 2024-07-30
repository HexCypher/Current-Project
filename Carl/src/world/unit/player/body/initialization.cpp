#include <iostream>
#include <windows.h>
#include "console.h"

// Function to set the console window always on top and resize it
void setConsoleWindowProperties() {
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, HWND_TOPMOST, 0, 0, 500, 600, SWP_NOMOVE | SWP_NOSIZE); // Always on top
    MoveWindow(consoleWindow, 0, 5, 500, 600, TRUE); // Resize and position console
}
