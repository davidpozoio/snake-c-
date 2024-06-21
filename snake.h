#include <iostream>
#include "state-machine.h"

#pragma once

class Snake
{
    int speedX = 0;
    int speedY = 0;
    int size = 10;

    struct Segment
    {
        int x = 0;
        int y = 0;
        int previousX = 0;
        int previousY = 0;
    };

    struct Point
    {
        int x = 0;
        int y = 0;
    };

    Segment currentPosition;

    Segment *segments = (Segment *)malloc(size * sizeof(Segment));

    Point limitPoint;

public:
    enum Direction
    {
        DirectionUp = 119,
        DirectionDown = 115,
        DirectionRight = 100,
        DirectionLeft = 97
    };

private:
    std::map<Direction, State<Direction>> directionStateMachine;
    Direction currentState = DirectionRight;

public:
    Snake();
    void moveTo(Direction direction);
    void init();
    void draw();
    void createSegment();
    void calculateSegmentsPosition();
    void setLimitPoint(unsigned int x, unsigned int y);
    bool calculateCollisionBody();
    bool calculateCollisionLimits();

    bool isPositionOcuppied(int x, int y);

    int getX();
    int getY();

    ~Snake()
    {
        free(this->segments);
    }
};