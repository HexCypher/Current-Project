#ifndef FEET_H
#define FEET_H

#include <dinput.h>

extern LPDIRECTINPUT8 dInput;
extern LPDIRECTINPUTDEVICE8 dKeyboard;

bool initializeDirectInput(HINSTANCE hInstance);
void turnCharacter(float currentFacing, float targetFacing);

#endif // FEET_H
