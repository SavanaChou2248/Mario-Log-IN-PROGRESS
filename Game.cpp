/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

Brief Overview:
This source file, "Game.cpp," defines the implementation of the Game class, responsible for managing the game's logic, levels, and interactions between the player character (Mario) and the game world.

*/

#include "Game.h"
#include <iostream>
#include <cstdlib>


using namespace std;

//Contructor, initializes a Game object with a specified game world, number of lives, and seed for randomization.
Game::Game(World* gameWorld, int numLives, int seed){
    m_numLives = numLives;
    m_gameWorld = gameWorld;
    m_gameResult = false;
    m_seed = seed;
    gameMario = new Mario(m_numLives, m_gameWorld);
}

//Destructor for the game class
Game::~Game(){
    delete gameMario;
}

/*
Name: setifLevelWon
Description: sets the game result if level was won or not
*/
void Game::setifLevelWon(bool gameResult){
    m_gameResult = gameResult;
}

/*
Name: ifLevelWon
Description: returns the game restul
*/
bool Game::ifLevelWon() {
    return m_gameResult;
}

/*
Name: gameLevel
Description: handles the gameplay logic for regular game level
*/
void Game::gameLevel(ofstream& fileOutput) {
    m_gameWorld->generateGrid(m_seed);
    gameMario->printInformation(fileOutput);
    m_gameWorld->printWorld(fileOutput);
    fileOutput << "---------------------------" << endl << endl;
    m_gameWorld->placeNothing(m_gameWorld->getMarioX(),m_gameWorld->getMarioY());
    gameMario->moveMario(fileOutput);
    if(gameMario->getifWin() && getMario()->getNumLives() > 0) {
        setifLevelWon(true);
    }
}

/*
Name: lastLevel
Description: handles the gameplay logic for the last game level
*/
void Game::lastLevel(ofstream& fileOutput) {
    m_gameWorld->generateLastGrid(m_seed);
    gameMario->printInformation(fileOutput);
    m_gameWorld->printWorld(fileOutput);
    fileOutput << "---------------------------" << endl;
    m_gameWorld->placeNothing(m_gameWorld->getMarioX(),m_gameWorld->getMarioY());
    gameMario->moveMario(fileOutput);
    if(gameMario->getifWin() && getMario()->getNumLives() > 0) {
        setifLevelWon(true);
    }
}

/*
Name: getMario
Description: returns a pointer to the mario character
*/
Mario* Game::getMario() {
    return gameMario;
}