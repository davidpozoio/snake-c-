#include <sys/ioctl.h>
#include <unistd.h>

#pragma once

class Utils
{
private:
    winsize size;

public:
    Utils()
    {
        ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
    }

    unsigned int getRows()
    {
        return size.ws_row;
    }

    unsigned int getCols()
    {
        return size.ws_col;
    }
};