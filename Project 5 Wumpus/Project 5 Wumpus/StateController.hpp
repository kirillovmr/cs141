//
//  StateController.hpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 8/3/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef StateController_hpp
#define StateController_hpp

struct State {
    int playerRoom = -1, wumpusRoom = -1, arrowRoom = -1;
    int batRooms[2] = {-1, -1}, pitRooms[2] = {-1, -1};
};


class StateNode {
public:
    State state;
    StateNode* pNext;
};


class StateController {
private:
    int m_length = 0;
    StateNode* m_pHead;
    
public:
    void appendState(State state);
    
    bool revertState();
    State getState();
    
    void eraseAll();
};

#endif /* StateController_hpp */
