#include <main.h>

using namespace std;

// Move mouse pointer
/*
void move (Display *display, int x, int y)
{
    XWarpPointer (display, None, DefaultRootWindow(display), 0,0,0,0, x, y);
    XFlush (display);
    usleep (1);
}
*/

int main()
{
    Display *display;
    display = XOpenDisplay(NULL);

    bool quit = false;
    while (!quit) {
        int dev_number = 0;
        while (esc_setup(("/dev/ttyUSB" + std::to_string(dev_number)).c_str()) == -1) {
            std::cout << "searching for connection /dev/ttyUSB" << dev_number << "\n";
            dev_number++;
            if(dev_number > 7) dev_number = 0;
            SDL_Delay(500);
        }

        std::cout << "connection found /dev/ttyUSB" << dev_number << "\n";

        bool localQuit = false;
        while (!quit && !localQuit) {
            std::string serialLine;
            int sre = serialRead(&serialLine);
            if(sre == 1) {
                if(serialLine.at(0) == 'K') {
                    serialLine.erase(0, 1);
                    std::cout << "key " << serialLine << " \n";
                    pressKey(display, serialLine.at(0));
                }
                else {
                    std::cout << "key release\n";
                    releaseLastPressedKey(display);
                }

                if(serialLine.at(0) == 'M') {
                    serialLine.erase(0, 1);
                    std::cout << "mouse " << serialLine << " \n";
                    clickButton(display, stoi(serialLine));
                }
                else {
                    std::cout << "mouse release\n";
                    releaseLastClickedButton(display);
                }
            }
            else if(sre == -1) localQuit = true;
        }
    }

    esc_quit();
    XCloseDisplay(display);
}
