/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

*/

#ifndef TESTLEVEL_H
#define TESTLEVEL_H
#include "World.h"
#include "Mario.h"
#include <fstream>

class Game;

using namespace std;

class testLevel {
public:
    testLevel(int numLevels, int numLives, World* world);
    virtual ~testLevel();
    int getNumLevels();
    void generateLevels(ofstream& fileOutput);
    void printInformation(ofstream& fileOutput, int index);
private:
    int m_numLevels;
    int m_numLives;
    World* m_world;
    Game** levelArr;
    int seed;

    // ofstream m_fileOutput;
};
#endif