/*
Savana Chou
2428859
sachou@chapman.edu
CPSC350-02
Programming Assignment 2: Not So Super Mario Bros.

*/

#include "World.h"
#include "Mario.h"
#include "Game.h"
#include "testLevel.h"
#include "FileLog.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

    const string inputFile = argv[1];
    const string outputFile = argv[2];
    
    FileLog myLog(inputFile, outputFile);
    myLog.playGame();

}