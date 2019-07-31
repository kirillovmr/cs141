//
//  Game.cpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 7/30/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime>
#include "Game.hpp"

using namespace std;

Game::Game() {
    // Setting up room number
    for (int i=0; i<20; i++)
        rooms[i].setNumber(i+1);
    
    // Setting up room connections.
    // Since rooms are array of nodes, Room 6 is rooms[5] and so on.
    rooms[0].setAdjacents(rooms[1], rooms[4], rooms[7]);
    rooms[1].setAdjacents(rooms[0], rooms[2], rooms[9]);
    rooms[2].setAdjacents(rooms[1], rooms[3], rooms[11]);
    rooms[3].setAdjacents(rooms[2], rooms[4], rooms[13]);
    rooms[4].setAdjacents(rooms[0], rooms[3], rooms[5]);
    rooms[5].setAdjacents(rooms[4], rooms[6], rooms[14]);
    rooms[6].setAdjacents(rooms[5], rooms[7], rooms[16]);
    rooms[7].setAdjacents(rooms[0], rooms[6], rooms[9]);
    rooms[8].setAdjacents(rooms[7], rooms[9], rooms[17]);
    rooms[9].setAdjacents(rooms[1], rooms[8], rooms[10]);
    rooms[10].setAdjacents(rooms[9], rooms[11], rooms[18]);
    rooms[11].setAdjacents(rooms[2], rooms[10], rooms[12]);
    rooms[12].setAdjacents(rooms[11], rooms[13], rooms[19]);
    rooms[13].setAdjacents(rooms[3], rooms[12], rooms[14]);
    rooms[14].setAdjacents(rooms[5], rooms[13], rooms[15]);
    rooms[15].setAdjacents(rooms[14], rooms[16], rooms[19]);
    rooms[16].setAdjacents(rooms[6], rooms[15], rooms[17]);
    rooms[17].setAdjacents(rooms[8], rooms[16], rooms[18]);
    rooms[18].setAdjacents(rooms[10], rooms[17], rooms[19]);
    rooms[19].setAdjacents(rooms[12], rooms[15], rooms[18]);
}

int* Game::getRandomNonRepeatingNumbers(int rangeFrom, int rangeTo, int howMany) {
    int totalNum = rangeTo-rangeFrom;
    int numbers[totalNum];
    for (int i=0; i<totalNum; i++)
        numbers[i] = rangeFrom+i;
    
    srand(static_cast<unsigned int>(time(0)));
    
    int* random = new int[howMany];
    for (int i=0; i<howMany; i++) {
        int randNum = rand() % (totalNum-i);
        random[i] = numbers[randNum];
        
        int temp = numbers[randNum];
        numbers[randNum] = numbers[totalNum-1-i];
        numbers[totalNum-1] = temp;
    }
    
    return random;
}

void Game::init() {
//    cout << rooms[15].getAdjacents()[1]->getNumber() << endl;
    int* randomNums = Game::getRandomNonRepeatingNumbers(0, 20, 5);
    for (int i=0; i<5; i++) {
        cout << randomNums[i] << " ";
    }
}
