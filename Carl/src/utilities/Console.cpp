#include <iostream>
#include <windows.h>
#include "console.h"

// Global variable
bool botActive = false;

// Function to toggle the bot's active state
void toggleBotActive() {
    botActive = !botActive;
    std::cout << "Bot is now " << (botActive ? "active" : "inactive") << std::endl;
}
