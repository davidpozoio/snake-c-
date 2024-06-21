#include "./apple.h"
#include <ncurses.h>
#include <cstdlib>
#include <iostream>

void Apple::draw()
{
    mvprintw(this->y, this->x, "M");
    refresh();
}

void Apple::generateRandomPosition()
{
    srand(time(nullptr));
    this->x = rand() % (this->xMax - this->xMin) + this->xMin;
    this->y = rand() & (this->yMax - this->yMin) + this->yMin;
}

int Apple::getX()
{
    return this->x;
}

int Apple::getY()
{
    return this->y;
}