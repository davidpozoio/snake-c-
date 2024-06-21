#include <ncurses.h>
#include "snake.h"

Snake::Snake()
{
    this->directionStateMachine[DirectionUp] = {
        DirectionUp,
        {{DirectionUp, DirectionUp},
         {DirectionDown, DirectionUp},
         {DirectionLeft, DirectionLeft},
         {DirectionRight, DirectionRight}}};

    this->directionStateMachine[DirectionDown] = {
        DirectionDown,
        {{DirectionUp, DirectionDown},
         {DirectionDown, DirectionDown},
         {DirectionLeft, DirectionLeft},
         {DirectionRight, DirectionRight}}};

    this->directionStateMachine[DirectionLeft] = {
        DirectionLeft,
        {{DirectionUp, DirectionUp},
         {DirectionDown, DirectionDown},
         {DirectionLeft, DirectionLeft},
         {DirectionRight, DirectionLeft}}};

    this->directionStateMachine[DirectionRight] = {
        DirectionRight,
        {{DirectionUp, DirectionUp},
         {DirectionDown, DirectionDown},
         {DirectionLeft, DirectionRight},
         {DirectionRight, DirectionRight}}};
}

void Snake::moveTo(Direction direction)
{
    switch (this->directionStateMachine[currentState].output)
    {
    case Direction::DirectionUp:
        speedX = 0;
        speedY = -1;
        break;
    case Direction::DirectionDown:
        speedX = 0;
        speedY = 1;
        break;
    case Direction::DirectionRight:
        speedY = 0;
        speedX = 1;
        break;
    case Direction::DirectionLeft:
        speedY = 0;
        speedX = -1;
        break;
    default:
        break;
    }

    ;
    auto it = this->directionStateMachine[currentState].next.find(direction);

    if (it == this->directionStateMachine[currentState].next.end())
    {
        return;
    }
    currentState = this->directionStateMachine[currentState].next[direction];
}

void Snake::draw()
{
    this->currentPosition.previousX = this->currentPosition.x;
    this->currentPosition.previousY = this->currentPosition.y;

    this->currentPosition.y += this->speedY;
    this->currentPosition.x += this->speedX;
    mvprintw(this->currentPosition.y, this->currentPosition.x, "x");
    refresh();
}

void Snake::createSegment()
{
    this->size++;
    this->segments = (Segment *)realloc(this->segments, this->size * sizeof(Segment));
}

void Snake::init()
{
    this->currentPosition.x = this->size + 1;

    for (int i = 0; i < this->size; i++)
    {
        this->segments[i].x = this->size - 1;
    }
}

void Snake::calculateSegmentsPosition()
{
    this->segments[0].previousX = this->segments[0].x;
    this->segments[0].previousY = this->segments[0].y;

    this->segments[0].x = this->currentPosition.previousX;
    this->segments[0].y = this->currentPosition.previousY;

    mvprintw(this->segments[0].y, this->segments[0].x, "a");

    for (int i = 1; i < this->size; i++)
    {
        this->segments[i].previousX = this->segments[i].x;
        this->segments[i].previousY = this->segments[i].y;
        this->segments[i].x = this->segments[i - 1].previousX;
        this->segments[i].y = this->segments[i - 1].previousY;

        mvprintw(this->segments[i].y, this->segments[i].x, "0");
    }

    refresh();
}

void Snake::setLimitPoint(unsigned int x, unsigned int y)
{
    this->limitPoint.x = x;
    this->limitPoint.y = y;
}

bool Snake::calculateCollisionLimits()
{
    if (this->currentPosition.x < 0 || this->currentPosition.x > this->limitPoint.x)
    {
        return true;
    }

    if (this->currentPosition.y < 0 || this->currentPosition.y > this->limitPoint.y)
    {
        return true;
    }

    return false;
}

bool Snake::calculateCollisionBody()
{
    for (int i = 1; i < this->size; i++)
    {
        if (this->segments[i].x == this->currentPosition.x && this->segments[i].y == this->currentPosition.y)
        {
            return true;
        }
    }

    return false;
}

bool Snake::isPositionOcuppied(int x, int y)
{
    if (this->currentPosition.x == x && this->currentPosition.y == y)
    {
        return true;
    }

    for (int i = 0; i < this->size; i++)
    {
        if (this->segments[i].x == x && this->segments[i].y == y)
        {
            return true;
        }
    }

    return false;
}

int Snake::getX()
{
    return this->currentPosition.x;
}

int Snake::getY()
{
    return this->currentPosition.y;
}