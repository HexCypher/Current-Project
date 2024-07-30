#include <iostream>
#include <windows.h>
#include "feet.h"

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
        std::cout << "Turn right" << std::endl; // Placeholder for actual turning logic
    }
    else {
        std::cout << "Turn left" << std::endl; // Placeholder for actual turning logic
    }
}
