#include "serial.h"

char dataArray[256];
std::string dataLine;
std::string previouslyDataLine;

int serialRead(std::string *output)
{
    int result = -1;



    if(esc_readuntil(dataArray, 256, '\n') == 0) {
        dataLine = dataArray;
        result = 0;
        if(dataLine != previouslyDataLine) result = 1;
        previouslyDataLine = dataLine;
        *output = dataLine;
    }
    return result;
}
