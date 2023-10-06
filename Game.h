/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

*/

#ifndef GAME_H
#define GAME_H
#include "World.h"
#include "Mario.h"
#include <fstream>

using namespace std;

class Game {
public:
    Game(World* gameWorld, int numLives, int seed);
    virtual ~Game();
    void setifLevelWon(bool gameResult);
    bool ifLevelWon();

    void gameLevel(ofstream& fileOutput);
    void lastLevel(ofstream& fileOutput);
    Mario* getMario();
private:
    World* m_gameWorld;
    Mario* gameMario;
    int m_numLives;
    bool m_gameResult;
    int m_seed;
};

#endif