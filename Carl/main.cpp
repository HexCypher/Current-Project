// Main.cpp
#include <iostream>
#include "Permissions.h"
#include "Recall.h"

int main() {
    if (!Permissions::EnableDebugPrivilege()) {
        std::cerr << "Failed to enable debug privileges" << std::endl;
        return 1;
    }

    DWORD pid = 1234; // Example PID, replace with actual game process ID
    Recall recall(pid);

    // Example: reading an integer value from a specific memory address
    LPCVOID baseAddress = (LPCVOID)0x00ABCDEF; // Example address
    int value = recall.ReadMemory<int>(baseAddress);
    std::cout << "Value: " << value << std::endl;

    return 0;
}
