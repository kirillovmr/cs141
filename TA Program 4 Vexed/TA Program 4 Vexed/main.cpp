//
//  main.cpp
//  TA Program 4 Vexed
//
//  Created by Viktor Kirillov on 10/14/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <string>

#include "AllBoards.hpp"
#include "Board.hpp"

using namespace std;

void displayDirections() {
    cout << "Welcome to Vexed!  \n"
         << "The objective is to place identical pieces next to each other, so that they vanish,  \n"
         << "clearing the board completely within the indicated number of moves. On each move you \n"
         << "may enter 'x' to exit the program, or 'r' to reset the current level.                \n"
         << endl;
}

void exitProgram() {
    cout << endl << "Ending program." << endl;
    exit(-1);
}

int main(int argc, const char * argv[]) {
    
    AllBoards allTheBoards;     // Reads in and stores all the boards from a data file
    Board theBoard;
    
    int currentBoardIndex = 0;  // Starting board index
    int step;
    char inputChar;
    int inputNum1;
    
    displayDirections();
    
    // Levels loop
    for (currentBoardIndex = 0; currentBoardIndex < MaxNumberOfBoards; currentBoardIndex++) {
        theBoard = allTheBoards.getBoard(currentBoardIndex);
        theBoard.displayBoard();
        step = 1;
    
        // Game loop
        while(true) {
            cout << "Move " << step << ". Enter 'm <fromRow><fromCol> <direction>': ";
            cin >> inputChar;
            if (inputChar == 'x' || inputChar == 'X')
                exitProgram();
            
            else if (inputChar == 'r' || inputChar == 'R') {
                currentBoardIndex--;
                cout << endl;
                break;
            }
            
            else if (inputChar == 's' || inputChar == 'S') {
                cin >> inputNum1;
                currentBoardIndex = inputNum1 - 1;
                cout << endl;
                break;
            }
            
            else if (inputChar == 'm' || inputChar == 'M') {
                cin >> inputChar >> inputNum1;
                int fromIndex = (inputChar-65) * BoardColumns + inputNum1;
                
                cin >> inputChar >> inputNum1;
                int toIndex = (inputChar-65) * BoardColumns + inputNum1;
                
                if (theBoard.move(fromIndex, toIndex)) {
                    step++;
                    cout << endl;
                    theBoard.displayBoard();
                    
                    if (theBoard.getNonEmptyTiles() == 0) {
                        cout << "Congratulations. You solved that level" << endl;
                        break;
                    }
                }
                
            }
        }
    }
    
    exitProgram();
    
    return 0;
}
