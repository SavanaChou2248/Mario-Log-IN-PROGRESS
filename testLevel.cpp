/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

Brief Overview:
This source file, "testLevel.cpp," defines the implementation of the testLevel class, which manages multiple levels of the game (Game class). It creates and handles instances of the Game class, tracks the number of levels, and generates and plays each level.

*/

#include "testLevel.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Game.h"
#include "World.h"
#include "Mario.h"

using namespace std;

//Constructor, initializes a testLevel object with the specified number of levels, initial lives, and game world.
testLevel::testLevel(int numLevels, int numLives, World* world) {
    m_numLevels = numLevels;
    m_numLives = numLives;
    m_world = world;
    levelArr = new Game*[numLevels];
}

//Destructor for the testLevel class
testLevel::~testLevel(){
    for (int i = 0; i < m_numLevels; ++i) {
        delete levelArr[i];
    }
    delete[] levelArr;
}

/*
Name: getNumLevels
Description: returns the total number of levels
*/
int testLevel::getNumLevels() {
    return m_numLevels;
}

/*
Name: generateLevels
Description: generates and plays each level, tracking the player's progress and outcomes
*/
void testLevel::generateLevels(ofstream& fileOutput) {
    for (int i = 0; i < m_numLevels; ++i) {
        unsigned int seed = static_cast<unsigned int>(time(nullptr)) + i;
        levelArr[i] = new Game(m_world, m_numLives, seed);
        if (i > 0) {
            levelArr[i]->getMario()->setNumLives(levelArr[i - 1]->getMario()->getNumLives());
            levelArr[i]->getMario()->setPowerLevel(levelArr[i - 1]->getMario()->getPowerLevel());
            levelArr[i]->getMario()->setNumCoins(levelArr[i - 1]->getMario()->getNumCoins());
            levelArr[i]->getMario()->setNumDefeated(levelArr[i - 1]->getMario()->getNumDefeated());
            levelArr[i]->getMario()->setNumMoves(levelArr[i - 1]->getMario()->getNumMoves());
        }

        if (i == m_numLevels - 1) {
            fileOutput << "---------------------------" << endl;
            fileOutput << "Level: " << i + 1 << endl;
            levelArr[i]->lastLevel(fileOutput);
        } else {
            fileOutput << "---------------------------" << endl;
            fileOutput << "Level: " << i + 1 << endl;
            levelArr[i]->gameLevel(fileOutput);
        }
       
        if(levelArr[i]->ifLevelWon()) {
            if (i == m_numLevels - 1) {
                fileOutput << "Mario won the game! Total number of moves: " << levelArr[i]->getMario()->getNumMoves() << endl;
            } else {
                fileOutput << "Mario won this level! Moving onto the next..." << endl << endl;
            }
        } else {
            fileOutput << "Mario lost the game... total number of moves: " << levelArr[i]->getMario()->getNumMoves() << endl;
            exit(0);
        }
    }
}

/*
Name: printInformation
Description: prints information about mario's position, power level, for given level as a argument
*/
void testLevel::printInformation(ofstream& fileOutput, int index) {
    fileOutput << "Position[row,column]: [" << m_world->getMarioX() << "," << m_world->getMarioY() << "]" << endl;
    fileOutput << "Power level: " << levelArr[index]->getMario()->getPowerLevel() << endl;
}