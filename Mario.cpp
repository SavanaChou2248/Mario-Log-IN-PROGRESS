/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

Brief Overview:
This source file, "Mario.cpp," defines the implementation of the Mario class, which represents the player character in the game. This class manages Mario's attributes, actions, interactions with the game world, and gameplay mechanics.

*/

#include "Mario.h"
#include "World.h"
#include "FileLog.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Constructor, initializes a Mario object with the specified number of lives and a pointer to the game world.
Mario::Mario(int numLives, World* world) {
    m_numLives = numLives;
    m_world = world;
    m_numCoins = 0;
    m_numPL = 0;
    m_numDefeated = 0;
    m_conditionWarp = false;
    m_conditionWin = false;
    m_numMoves = 0;
    srand(static_cast<unsigned>(time(nullptr)));
}

//Destructor
Mario::~Mario(){

}

/*
Name: setNumCoins
Description: sets the number of coins collected by mario
*/
void Mario::setNumCoins(int numCoins) {
    m_numCoins = numCoins;
}

/*
Name: setNumLives
Description: sets the number of lives mario has
*/
void Mario::setNumLives(int numLives) {
    m_numLives = numLives;
}

/*
Name: setPowerLevel
Description: sets mario's power level
*/
void Mario::setPowerLevel(int numPL) {
    m_numPL = numPL;
}

/*
Name: setNumDefeated
Description: sets the number of enemeis defeaated by mario
*/
void Mario::setNumDefeated(int numDefeated) {
    m_numDefeated = numDefeated;
}

/*
Name: getNumCoins
Description: returns the number of coins collected by mario
*/
int Mario::getNumCoins() {
    return m_numCoins;
}

/*
Name: getNumLives
Description: returns the number of lives mario has
*/
int Mario::getNumLives() {
    return m_numLives;
}

/*
Name: getPowerLevel
Description: returns mario's power level
*/
int Mario::getPowerLevel() {
    return m_numPL;
}

/*
Name: getNumDefeated
Description: returns the number of enemies mario has defeated
*/
int Mario::getNumDefeated(){
    return m_numDefeated;
}

/*
Name: moveaMario
Description: Moves Mario ranomly within the game world and handles interactions.
*/
void Mario::moveMario(ofstream& fileOutput) {
    ++m_numMoves;
    m_xMario = m_world->getMarioX();
    m_yMario = m_world->getMarioY();
    int direction = rand() % 4;
    if (direction == 0) { //left
        fileOutput << endl << "Move: left" << endl;
        m_yMario = (m_yMario - 1 + m_world->getGridSize()) % m_world->getGridSize();
        m_world->setMarioY(m_yMario);
        m_world->setMarioX(m_xMario);
        interact(fileOutput);
    } else if (direction == 1) { //right
        fileOutput << endl << "Move: right" << endl;
        m_yMario = (m_yMario + 1) % m_world->getGridSize();
        m_world->setMarioY(m_yMario);
        m_world->setMarioX(m_xMario);
        interact(fileOutput);
    } else if (direction == 2) { //up
        fileOutput << endl << "Move: up" << endl;
        m_xMario = (m_xMario - 1 + m_world->getGridSize()) % m_world->getGridSize();
        m_world->setMarioY(m_yMario);
        m_world->setMarioX(m_xMario);
        interact(fileOutput);
    } else if (direction == 3) { //down
        fileOutput << endl << "Move: down" << endl;
        m_xMario = (m_xMario + 1) % m_world->getGridSize();
        m_world->setMarioY(m_yMario);
        m_world->setMarioX(m_xMario);
        interact(fileOutput);
    }

}

/*
Name: encounterNothing
Description: handles mario's interaction with an empty space in the game world
*/
void Mario::encounterNothing(ofstream& fileOutput){
    m_world->placeNothing(m_world->getMarioX(), m_world->getMarioY());
    moveMario(fileOutput);
}

/*
Name: collectCoin
Description: handles mario's collection of coins and potential life gain
*/
void Mario::collectCoin(ofstream& fileOutput) {
    ++m_numCoins;
    if (m_numCoins == 20) {
        ++m_numLives;
        fileOutput << "Mario gained a life!" << endl;
        m_numCoins = 0;
    }
    m_world->placeNothing(m_world->getMarioX(), m_world->getMarioY());
    moveMario(fileOutput);
}

/*
Name: consumeMushroom
Description: handles mario's consumption of mushrooms and power level increase 
*/
void Mario::consumeMushroom(ofstream& fileOutput) {
    if (m_numPL < 2) {
        ++m_numPL;
    }
    m_world->placeNothing(m_world->getMarioX(), m_world->getMarioY());
    moveMario(fileOutput);
}

/*
Name: gainLife
Description: handles mario's life gain when defeating a certain number of enemies
*/
void Mario::gainLife(ofstream& fileOutput) {
    if (m_numDefeated == 7) {
        fileOutput << "Mario gains a life for defeating 7 enemies!" << endl;
        ++m_numLives;
    }
}

/*
Name: engageGoomba
Description: handles mario's interaction with a goomba enemy
*/
void Mario::engageGoomba(ofstream& fileOutput) {
    int probability = rand() % 100;
    if (probability < 80) {
        m_world->placeNothing(m_world->getMarioX(), m_world->getMarioY());
        fileOutput << "Mario won the battle!" << endl;
        ++m_numDefeated;
        gainLife(fileOutput);
        moveMario(fileOutput);
    } else {
        if (m_numPL > 0) {
            m_world->placeGoomba(m_world->getMarioX(), m_world->getMarioY());
            fileOutput << "Mario lost the battle and a PL... moving on" << endl;
            --m_numPL;
            moveMario(fileOutput);
        } else {
            --m_numLives;
            m_numDefeated = 0;
            if (m_numLives >= 1) {
                fileOutput << "Mario lost a life" << endl;
                engageGoomba(fileOutput);
            } else {
                fileOutput << "Mario died to the goomba" << endl;
                
            }
        }
    }

}

/*
Name: engageKoopa
Description: handles mario's interaction with a koopa enemy
*/
void Mario::engageKoopa(ofstream& fileOutput) {
    int probability = rand() % 100;
    if (probability < 65) {
        m_world->placeNothing(m_world->getMarioX(), m_world->getMarioY());
        fileOutput << "Mario won the battle!" << endl;
        ++m_numDefeated;
        gainLife(fileOutput);
        moveMario(fileOutput);
    } else {
        if (m_numPL > 0) {
            m_world->placeKoopa(m_world->getMarioX(), m_world->getMarioY());
            fileOutput << "Mario lost the battle and a PL... moving on" << endl;
            --m_numPL;
            moveMario(fileOutput);
        } else {
            --m_numLives;
            m_numDefeated = 0;
            if (m_numLives >= 1) {
                fileOutput << "Mario lost a life" << endl;
                engageGoomba(fileOutput);
            } else {
                fileOutput << "Mario died to the koopa" << endl;
            }
        }
    }
}

/*
Name: engageBoss
Description: handles mario's interaction with the boss enemy
*/
void Mario::engageBoss(ofstream& fileOutput) {
    int probability = rand() % 100;
    if (probability < 50) {
        fileOutput << "Mario won the battle!" << endl;
        ++m_numDefeated;
        gainLife(fileOutput);
        setifWin(true);
    } else {
        if (m_numPL > 1) {
            fileOutput << "Mario lost 2 PL fighting the boss" << endl;
            --m_numPL;
            --m_numPL;
            engageBoss(fileOutput);
        } else {
            if (m_numLives > 1) {
                    fileOutput << "Mario lost a life" << endl;
                    --m_numLives;
                    m_numDefeated = 0;
                    engageBoss(fileOutput);
            } else {
                fileOutput << "Mario died to the boss" << endl;
            }
        }
    }
}

/*
Name: setifWin
Description: sets the condition indicating whether mario has won the game
*/
void Mario::setifWin(bool conditionWin) {
    m_conditionWin = conditionWin;
}

/*
Name: getifWin
Description: returns the condition indicating whether mario has won the game
*/
bool Mario::getifWin() {
    return m_conditionWin;
}

/*
Name: interact
Description: handles mario's interaction with the game world elements by looking at marios position with the element at that position
*/
void Mario::interact(ofstream& fileOutput) {
    if(m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'c') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY()  + 1<< "]" << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Action: Coin collected" << endl;
        fileOutput << "Number of coins: " << getNumCoins() + 1 << endl;
        collectCoin(fileOutput);
    } else if (m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'm') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY() + 1 << "]" << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Action: Ate mushroom" << endl;
        fileOutput << "Number of coins: " << getNumCoins() << endl;
        consumeMushroom(fileOutput);
    } else if (m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'g') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY() + 1 << "]" << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Action: Encountered a goomba" << endl;
        fileOutput << "Number of coins: " << getNumCoins() << endl;
        engageGoomba(fileOutput);
    } else if (m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'k') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY() + 1 << "]" << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Action: Encountered a koopa" << endl;
        fileOutput << "Number of coins: " << getNumCoins() << endl;
        engageKoopa(fileOutput);
    } else if (m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'b') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY() + 1 << "]" << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Action: Encountered a boss" << endl;
        fileOutput << "Number of coins: " << getNumCoins() << endl;
        engageBoss(fileOutput);
    } else if (m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'w') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY() + 1 << "]" << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Action: warped" << endl;
        fileOutput << "Number of coins: " << getNumCoins() << endl;
        setifWin(true);
    } else if (m_world->getTileChar(m_world->getMarioX(), m_world->getMarioY()) == 'x') {
        m_world->placeMario(m_xMario,m_yMario);
        m_world->printWorld(fileOutput);
        fileOutput << "Position[row,column]: [" << m_world->getMarioX() + 1 << "," << m_world->getMarioY() + 1 << "]" << endl;
        fileOutput << "Power level: " << getPowerLevel() << endl;
        fileOutput << "Number of lives: " << getNumLives() << endl;
        fileOutput << "Action: nothing" << endl;
        fileOutput << "Number of coins: " << getNumCoins() << endl;
        encounterNothing(fileOutput);
    }
}

/*
Name: printInformation
Description: prints mario's starting level attributes
*/
void Mario::printInformation(ofstream& fileOutput) {
    fileOutput << "Mario's Starting Level Attributes:" << endl;
    fileOutput << "Position[row,column]: [" << m_world->getMarioX() << "," << m_world->getMarioY() << "]" << endl;
    fileOutput << "Power level: " << getPowerLevel() <<  endl;
    fileOutput << "Number of lives: " << getNumLives() << endl;
    fileOutput << "Number of coins: " << getNumCoins() << endl;
}

/*
Name: setNumMoves
Description: sets the number of moves made by mario
*/
void Mario::setNumMoves(int numMoves) {
    m_numMoves = numMoves;
}

/*
Name: getNumMoves
Description: returns the number of moves made by mario
*/
int Mario::getNumMoves() {
    return m_numMoves;
}