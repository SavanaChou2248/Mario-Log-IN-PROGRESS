/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

*/

#ifndef FILELOG_H
#define FILELOG_H
#include <iostream>
#include <fstream>
#include "World.h"
#include "testLevel.h"

using namespace std;

class FileLog {
public:
    FileLog(const string& inputFile, const string& logFile);
    virtual ~FileLog();
    void playGame();
    void printThing();

private:
    string m_inputFile;
    string m_logFile;
    ifstream input;
    ofstream log;
    int numLevels;
    int gridSize;
    int numLives;
    int percCoin;
    int percNothing;
    int percGoomba;
    int percKoopa;
    int percMushroom;
    World* world;
    testLevel* levels;
};

#endif