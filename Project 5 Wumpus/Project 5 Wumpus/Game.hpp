//
//  Game.hpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 7/30/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <string>
#include <vector>
#include "Node.hpp"
#include "StateController.hpp"

class Game {
private:
    StateController m_sc;
    Node m_rooms[20];
    State m_state;
    
public:
    Game();
    void init(bool restart = false);
    void loop();
    void exitProgram();
    
    void drawMaze();
    void displayCheat();
    
    bool playerMove(int inputNum);
    bool playerShoot(std::vector<int> rooms);
    
    std::string getRoomDescription();
    int getEmptyRoom();
    
    void setState(State state);
    State getState();
    
    void setPlayerRoom(int r);
    int  getPlayerRoom();
    
    void setWumpusRoom(int r);
    int getWumpusRoom();
    
    void setArrowRoom(int r);
    int getArrowRoom();
    
    void setBatRooms(int r1, int r2);
    int* getBatRooms();
    
    void setPitRooms(int r1, int r2);
    int* getPitRooms();
    
    static int* getRandomNonRepeatingNumbers(int rangeFrom, int rangeTo, int howMany);
    static std::vector<int> parseIntegersFromCString(const char* str);
};

#endif /* Game_hpp */
