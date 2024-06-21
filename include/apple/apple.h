#pragma once

class Apple
{
    int x = 0;
    int y = 0;

    int xMax = 10;
    int xMin = 1;
    int yMax = 10;
    int yMin = 1;

public:
    Apple(int xMax, int xMin, int yMax, int yMin)
    {
        this->xMax = xMax;
        this->xMin = xMin;

        this->yMax = yMax;
        this->yMin = yMin;
    }

    void draw();
    void generateRandomPosition();
    int getX();
    int getY();
};