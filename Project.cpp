#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <cmath>
#include <windows.h>

const int MAP_WIDTH = 60;
const int MAP_HEIGHT = 20;

const char PLAYER_CHAR = '0';
const char OBSTACLE_CHAR = 'x';
const char EXIT_CHAR = '@';
const char BORDER_CHAR = '$';

const std::string PLAYER_COLOR = "\033[31m"; 
const std::string EXIT_COLOR = "\033[32m"; 
const std::string DEFAULT_COLOR = "\033[0m"; 

int playerX, playerY;
int exitX, exitY;

char map[MAP_HEIGHT][MAP_WIDTH];

int score = 0;

unsigned long startTime;
const int TIME_LIMIT = 20;

void placeElements() {

    playerX = rand() % (MAP_WIDTH - 2) + 1;
    playerY = rand() % (MAP_HEIGHT - 2) + 1;

    int minDistance = 30;
    do {
        exitX = rand() % (MAP_WIDTH - 2) + 1;
        exitY = rand() % (MAP_HEIGHT - 2) + 1;
    } while (abs(exitX - playerX) + abs(exitY - playerY) < minDistance);

    int numObstacles = (MAP_WIDTH - 2) * (MAP_HEIGHT - 2) / 3;
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {

            if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1) {
                map[y][x] = BORDER_CHAR;
            }
            else if (x == playerX && y == playerY) {
                map[y][x] = PLAYER_CHAR;  
            }
            else if (x == exitX && y == exitY) {
                map[y][x] = EXIT_CHAR;  
            }
            else if ((abs(x - exitX) <= 1 && abs(y - exitY) <= 1) || (abs(x - playerX) <= 1 && abs(y - playerY) <= 1)) {
                map[y][x] = ' ';  
            }
            else if (rand() % (MAP_WIDTH - 2) * (MAP_HEIGHT - 2) < numObstacles) {
                map[y][x] = OBSTACLE_CHAR;  
                numObstacles--;
            }
            else {
                map[y][x] = ' ';
            }
        }
    }

    startTime = GetTickCount();
}

void displayMap() {
    system("cls"); 

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            if (x == playerX && y == playerY) {
                std::cout << PLAYER_COLOR << map[y][x] << DEFAULT_COLOR;
            }
            else if (x == exitX && y == exitY) {
                std::cout << EXIT_COLOR << map[y][x] << DEFAULT_COLOR;
            }
            else {
                std::cout << map[y][x];
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Score: " << score << std::endl;

    unsigned long currentTime = GetTickCount();
    int remainingTime = TIME_LIMIT - static_cast<int>((currentTime - startTime) / 1000);
    std::cout << "Time: " << remainingTime << "s" << std::endl;

    if (remainingTime <= 0) {
        std::cout << "Time's up! Game over." << std::endl;
        exit(0);
    }
}

void movePlayer(int dx, int dy) {
   
    int newPlayerX = playerX + dx;
    int newPlayerY = playerY + dy;

    if (newPlayerX > 0 && newPlayerX < MAP_WIDTH - 1 &&
        newPlayerY > 0 && newPlayerY < MAP_HEIGHT - 1 &&
        map[newPlayerY][newPlayerX] != OBSTACLE_CHAR) {
        map[playerY][playerX] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;

        if (playerX == exitX && playerY == exitY) {
            score++;
            placeElements();
        }

        map[playerY][playerX] = PLAYER_CHAR;
    }

    displayMap();
}

int main() {

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    placeElements();

    displayMap();

    while (true) {

        char input = _getch();

        switch (input) {
        case 'w':
            movePlayer(0, -1);
            break;
        case 's':
            movePlayer(0, 1);
            break;
        case 'a':
            movePlayer(-1, 0);
            break;
        case 'd':
            movePlayer(1, 0);
            break;
        case 'q':
            return 0;  
        }
    }

    return 0;
}