PROJECT_DIR:=$(pwd)
INCLUDE=$(PROJECT_DIR)include
BUILD=$(PROJECT_DIR)build

default: main.o
	c++ $(BUILD)/apple.o $(BUILD)/snake.o $(BUILD)/main.o -lncurses -o a.out
apple.o:
	c++ -L$(INCLUDE) -c $(INCLUDE)/apple/apple-functions.cpp -o $(BUILD)/apple.o
snake.o: apple.o
	c++ -L$(INCLUDE) -c $(INCLUDE)/snake/snake-functions.cpp -o $(BUILD)/snake.o
main.o: snake.o
	c++ -L$(INCLUDE) -c main.cpp -lncurses -o $(BUILD)/main.o