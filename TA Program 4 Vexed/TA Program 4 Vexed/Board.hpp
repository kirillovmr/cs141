//
//  Board.hpp
//  TA Program 4 Vexed
//
//  Created by Viktor Kirillov on 10/14/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#pragma once

#include "Constants.h"
#include <vector>

class Board {
private:
    int m_level;
    int m_par;
    int m_board[BoardRows * BoardColumns];
    char m_boardChar[10] = {' ','&','@','+','%','^','#','=','*','.'};
    int m_nonEmptyTiles;
    
public:
    Board();
    Board(int boardNumber, int boardValues[BoardRows * BoardColumns], int par);
    
    int getNonEmptyTiles();
    
    bool move(int indexFrom, int indexTo);
    int checkForDrop(int indexFrom);
    bool destroyAdjacents(int indexFrom, std::vector<int> &idxToFall);
    
    void displayBoard();
};
