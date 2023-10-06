/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

Brief Overview:
This source file, "FileLog.cpp," defines the implementation of the FileLog class, which handles reading game configuration from an input file, logging game progress to an output file, and orchestrating the gameplay by creating instances of the World, testLevel, and Game classes.

*/

#include "FileLog.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

//Constructor, initializes a FileLog object with input and log file names, opens the files, and reads game configuration.
FileLog::FileLog(const string& inputFile, const string& logFile) {
    m_inputFile = inputFile;
    m_logFile = logFile;
    input.open(m_inputFile);
    log.open(m_logFile);

    input >> numLevels >> gridSize >> numLives >> percCoin >> percNothing >> percGoomba >> percKoopa >> percMushroom;
    
    world = new World(gridSize, percMushroom, percCoin, percGoomba, percKoopa, percNothing);
    levels = new testLevel(numLevels, numLives, world);
}

//Destructure, responsible for closing files and freeing memory 
FileLog::~FileLog() {
    input.close();
    log.close();
    delete world;
    delete levels;
}

/*
Name: playGame
Description: orchestrates the gameplay by generating and playing game levels using the levels object
*/
void FileLog::playGame() {
    levels->generateLevels(log);
}
