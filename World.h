/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

*/

#ifndef WORLD_H
#define WORLD_H

#include <fstream>
using namespace std;

class World {
public:
    World(int gridSize, int percMushroom, int percCoin, int percGoomba, int percKoopa, int percNothing);
    World();
    virtual ~World();
    int getGridSize();
    char** getGameWorld() const;
    void placeNothing(int x, int y);
    void placeMushroom(int x, int y);
    void placeCoin(int x, int y);
    void placeGoomba(int x, int y);
    void placeKoopa(int x, int y);
    void placeBoss(int x, int y);
    void placeWarpPipe(int x, int y);
    void placeMario(int x, int y);
    void setMarioX(int xPosition);
    int getMarioX();
    void setMarioY(int yPosition);
    int getMarioY();
    char getTileChar(int x, int y);
    void generateGrid(int seed);
    void generateLastGrid(int seed);
    void printWorld(ofstream& outputFile); 

private:
    int m_gridSize;
    char** gameWorld;
    int m_percNothing;
    int m_percMushroom;
    int m_percCoin;
    int m_percGoomba;
    int m_percKoopa;
    int m_xPosition;
    int m_yPosition;
};

#endif