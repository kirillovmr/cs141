//
//  Game.hpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 7/30/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Node.hpp"

class Game {
private:
    Node rooms[20];
    Node playerRoom;
    
public:
    Game();
    void init();
    
    static int* getRandomNonRepeatingNumbers(int rangeFrom, int rangeTo, int howMany);

};

#endif /* Game_hpp */
