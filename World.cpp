/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

Brief Overview:
This source file, "World.cpp," defines the implementation of the World class, which is responsible for generating and managing the game world grid game. It contains functions to initialize the grid, populate it with game elements (such as mushrooms, coins, enemies, and the player character), and print the grid to an output file.

*/

#include "World.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FileLog.h"

using namespace std;

//Constructor, initializes a World object with the specified grid size and probabilities for game elements.
World::World(int gridSize, int percMushroom, int percCoin, int percGoomba, int percKoopa, int percNothing){
    m_gridSize = gridSize;
    m_percMushroom = percMushroom;
    m_percCoin = percCoin;
    m_percGoomba = percGoomba;
    m_percKoopa = percKoopa;
    m_percNothing = percNothing;

    srand(static_cast<unsigned>(time(nullptr)));

    gameWorld = new char*[m_gridSize];
    for(int i = 0; i < m_gridSize; ++i) {
        gameWorld[i] = new char[m_gridSize];
    }

}

//default constructor 
World::World() {
    m_gridSize = 0;
    m_percMushroom = 0;
    m_percCoin = 0;
    m_percGoomba = 0;
    m_percKoopa = 0;
    m_percNothing = 0;

}

//Destructor to release dynamically allocated memory
World::~World() {
    for (int i = 0; i < m_gridSize; ++i) {
        delete[] gameWorld[i];
    }
    delete[] gameWorld;
}

/*
Name: getGridSize()
Description: returns the size of the game world grid
*/
int World::getGridSize() {
    return m_gridSize;
}

/*
Name: getGameWorld()
Description: returns a pointer to the game world grid
*/
char** World::getGameWorld() const {
    return gameWorld;
}

/*
Name: getTileChar()
Description: returns the character at the specified grid coordinates with the x and y position as parameters
*/
char World::getTileChar(int x, int y) {
    return gameWorld[x][y];
}

/*
Name: placeNothing()
Description: places the character x (nothing) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeNothing(int x, int y) {
    gameWorld[x][y] = 'x';
}

/*
Name: placeMushroom()
Description: places the character m (mushroom) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeMushroom(int x, int y) {
    gameWorld[x][y] = 'm';
}

/*
Name: placeCoin()
Description: places the character c (coin) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeCoin(int x, int y) {
    gameWorld[x][y] = 'c';
}

/*
Name: placeGoomba()
Description: places the character g (goomba) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeGoomba(int x, int y) {
    gameWorld[x][y] = 'g';
}

/*
Name: placeKoopa()
Description: places the character k (koopa) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeKoopa(int x, int y) {
    gameWorld[x][y] = 'k';
}

/*
Name: placeBoss()
Description: places the character b (boss) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeBoss(int x, int y) {
    gameWorld[x][y] = 'b';
}

/*
Name: placeWarpPipe()
Description: places the character w (warp pipe) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeWarpPipe(int x, int y) {
    gameWorld[x][y] = 'w';
}

/*
Name: placeMario()
Description: places the character H (Hero/Mario) at the specified grid coordinates with the x and y position as parameters
*/
void World::placeMario(int x, int y) {
    gameWorld[x][y] = 'H';
}

/*
Name: setMarioX()
Description: sets the x-coordinates of Mario
*/
void World::setMarioX(int xPosition) {
    m_xPosition = xPosition;
}

/*
Name: getMarioX()
Description: returns the x-coordinates of Mario
*/
int World::getMarioX() {
    return m_xPosition;
}

/*
Name: setMarioY()
Description: sets the y-coordinates of Mario
*/
void World::setMarioY(int yPosition) {
    m_yPosition = yPosition;
}

/*
Name: getMarioY()
Description: returns the y-coordinates of Mario
*/
int World::getMarioY() {
    return m_yPosition;
}

/*
Name: generateGrid
Description: Generates the game world grid with random elements based on the provided seed. Takes a seed as a parameter to ensure it will be random everytime
*/
void World::generateGrid(int seed) {
    srand(static_cast<unsigned>(seed));
    for (int x = 0; x < m_gridSize; ++x) {
        for (int y = 0; y < m_gridSize; ++y) {
            int random = rand() % 100;
            if (random < m_percCoin) {
                placeCoin(x, y);
            } else if (random < m_percCoin + m_percMushroom) {
                placeMushroom(x, y);
            } else if (random < m_percCoin + m_percMushroom + m_percGoomba) {
                placeGoomba(x, y);
            } else if (random < m_percCoin + m_percMushroom + m_percGoomba + m_percKoopa) {
                placeKoopa(x, y);
            } else if (random < m_percCoin + m_percMushroom + m_percGoomba + m_percKoopa + m_percNothing) {
                placeNothing(x, y);
            }
        }
    }
    int x = rand() % m_gridSize;
    int y = rand() % m_gridSize;
    placeBoss(x,y);
    while (gameWorld[x][y] == 'b') { //makes sure Mario doesn't replace boss
        x = rand() % getGridSize();
        y = rand() % getGridSize();
    }
    placeMario(x,y);
    setMarioX(x);
    setMarioY(y);
    while ((gameWorld[x][y] == 'b') ||(gameWorld[x][y] == 'H')) { //makes sure warp pipe doesnt replace mario or boss
        x = rand() % m_gridSize;
        y = rand() % m_gridSize;
    }
    placeWarpPipe(x,y);
}

/*
Name: generateLastGrid
Description: Generates the last game world grid of the levels with random elements based on the provided seed. (it doesnt contain a warp pipe) Takes a seed as a parameter to ensure it will be random everytime
*/
void World::generateLastGrid(int seed) {
    srand(static_cast<unsigned>(seed));
    for (int x = 0; x < m_gridSize; ++x) {
        for (int y = 0; y < m_gridSize; ++y) {
            int random = rand() % 100;
            if (random < m_percCoin) {
                placeCoin(x, y);
            } else if (random < m_percCoin + m_percMushroom) {
                placeMushroom(x, y);
            } else if (random < m_percCoin + m_percMushroom + m_percGoomba) {
                placeGoomba(x, y);
            } else if (random < m_percCoin + m_percMushroom + m_percGoomba + m_percKoopa) {
                placeKoopa(x, y);
            } else {
                placeNothing(x, y);
            }
        }
    }
    int x = rand() % m_gridSize;
    int y = rand() % m_gridSize;
    placeBoss(x,y);
    while (gameWorld[x][y] == 'b') {
        x = rand() % getGridSize();
        y = rand() % getGridSize();
    }
    placeMario(x,y);
    setMarioX(x);
    setMarioY(y);
}

/*
Name: printWorld
Description: Prints the game world grid to the specified output file given as the argument.
*/
void World::printWorld(ofstream& outputFile) {
    for (int x = 0; x < m_gridSize; ++x) {
        for (int y = 0; y < m_gridSize; ++y) {
            outputFile << gameWorld[x][y] << ' ';
        }
        outputFile << endl;
    }
}
