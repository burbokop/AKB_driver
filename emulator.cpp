#include "emulator.h"

int previouslyButtonCode = 0;
int previouslyKeyCode = 65;

void pressKey(Display *display, char key)
{
    previouslyKeyCode = XKeysymToKeycode(display, key);
    XTestFakeKeyEvent(display, previouslyKeyCode, 1, 0);
}

void releaseLastPressedKey(Display *display)
{
    XTestFakeKeyEvent(display, previouslyKeyCode, 0, 0);
}

int clickButton(Display *display, int button)
{
    XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = button;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer (display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    event.type = ButtonPress;
    if (XSendEvent (display, PointerWindow, True, ButtonPressMask, &event) == 0) return -1;
    else previouslyButtonCode = button;
    XFlush (display);
    usleep (1);
    return 0;
}

int releaseLastClickedButton(Display *display)
{
    XEvent event;
    memset (&event, 0, sizeof (event));
    event.xbutton.button = previouslyButtonCode;
    event.xbutton.same_screen = True;
    event.xbutton.subwindow = DefaultRootWindow (display);
    while (event.xbutton.subwindow)
    {
        event.xbutton.window = event.xbutton.subwindow;
        XQueryPointer (display, event.xbutton.window, &event.xbutton.root, &event.xbutton.subwindow, &event.xbutton.x_root, &event.xbutton.y_root, &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    }

    event.type = ButtonRelease;
    if (XSendEvent (display, PointerWindow, True, ButtonReleaseMask, &event) == 0) return -1;
    XFlush (display);
    usleep (1);
    return 0;
}
