#ifndef EMULATOR_H
#define EMULATOR_H

#include <SDL2/SDL.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>

void pressKey(Display *display, char key);
void releaseLastPressedKey(Display *display);
int clickButton(Display *display, int button);
int releaseLastClickedButton(Display *display);

#endif // EMULATOR_H
