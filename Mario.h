/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

*/

#ifndef MARIO_H
#define MARIO_H
#include "testLevel.h"
#include <fstream>

using namespace std;

class Mario {
public:
    Mario(int numLives, World* world);
    virtual ~Mario();
    void setNumCoins(int numCoins);
    void setNumLives(int numLives);
    void setPowerLevel(int numPL);
    void setNumDefeated(int numDefeated);
    int getNumCoins();
    int getNumLives();
    int getPowerLevel();
    int getNumDefeated();
    void moveMario(ofstream& fileOutput);
    void encounterNothing(ofstream& fileOutput);
    void collectCoin(ofstream& fileOutput);
    void consumeMushroom(ofstream& fileOutput);
    void engageGoomba(ofstream& fileOutput);
    void engageKoopa(ofstream& fileOutput);
    void engageBoss(ofstream& fileOutput);
    void gainLife(ofstream& fileOutput);
    void setencounterWarpPipe(bool conditionWarp);
    bool getencounterWarpPipe();
    void setifWin(bool conditionWin);
    bool getifWin();
    void interact(ofstream& fileOutput);
    void printInformation(ofstream& fileOutput);
    void setNumMoves(int numMoves);
    int getNumMoves();
    
private:
    int position;
    int direction;
    int m_numMoves;
    int m_numPL;
    int m_numLives;
    int m_numCoins;
    int m_numDefeated;
    string m_move;
    World* m_world;
    int m_xMario;
    int m_yMario;
    bool m_conditionWarp;
    bool m_conditionWin;
    World* m_currLevel;
};

#endif