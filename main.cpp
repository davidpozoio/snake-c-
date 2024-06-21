#include <ncurses.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "include/snake/snake.h"
#include "include/apple/apple.h"
#include "include/utils/utils.h"

void delay(std::chrono::milliseconds milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

int main()
{
    const int DELAY_MILLISECONDS = 50;
    const int EXIT_KEY = 27;
    bool startGame = true;

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true);
    cbreak();
    timeout(0);

    Utils utils;

    Snake snake;
    snake.moveTo(Snake::DirectionRight);
    snake.setLimitPoint(utils.getCols(), utils.getRows());

    Apple apple(utils.getCols() - 1, 1, utils.getRows() - 1, 1);

    apple.generateRandomPosition();
    apple.draw();

    while (startGame)
    {

        int key = getch();

        if (key == EXIT_KEY)
        {
            break;
        }

        snake.moveTo((Snake::Direction)key);
        snake.draw();
        snake.calculateSegmentsPosition();

        bool hasSnakeCollisioned = snake.calculateCollisionBody() || snake.calculateCollisionLimits();

        if (hasSnakeCollisioned)
        {
            startGame = false;
            break;
        }

        if (snake.getX() == apple.getX() && snake.getY() == apple.getY())
        {
            apple.generateRandomPosition();

            snake.createSegment();
        }

        if (snake.isPositionOcuppied(apple.getX(), apple.getY()))
        {
            apple.generateRandomPosition();
            delay((std::chrono::milliseconds)DELAY_MILLISECONDS);
            clear();
            continue;
        }

        apple.draw();

        delay((std::chrono::milliseconds)DELAY_MILLISECONDS);
        clear();
    }
    nocbreak();
    timeout(1000);
    getch();
    endwin();
}