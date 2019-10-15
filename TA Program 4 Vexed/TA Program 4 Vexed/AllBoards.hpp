//
//  AllBoards.hpp
//  TA Program 4 Vexed
//
//  Created by Viktor Kirillov on 10/14/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#pragma once

#include <iostream>   // For cin, cout
#include <fstream>    // For file input
#include <cstring>    // For fgets()

#include "Board.hpp"
#include "Constants.h"

using namespace std;

void displayDirections();

class AllBoards {
    public:
        // Constructor
        AllBoards() {
            // Read in all the boards from the data file
            ifstream inputFileStream;  // declare the input file stream

            // Open input file and verify file open worked.
            inputFileStream.open( FileName);
            if( !inputFileStream.is_open()) {
                cout << "Could not find input file. " << FileName << ".  Exiting..." << endl;
                exit( -1);
            }

            // Read the five lines of comments at the top of the datafile.  Datafile structure is:
            //    // Originally from Vexed v2.0 - globals.c "Global variable declarations"
            //    // Copyright (C) 1999 James McCombe (cybertube@earthling.net)
            //    // September 1,2001 - Version 2.0 changes by Mark Ingebretson (ingebret@yahoo.com) and others.
            //    // Oct 13, 2019  Format changed by Dale Reed (reed @ uic.edu)
            //    // Covered by the GNU General Public License https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
            //    // Level 000
            //    9 9 9 9 9 9 9 9 9 9
            //    9 9 9 9 9 9 9 9 9 9
            //    9 9 9 2 1 0 0 9 9 9
            //    9 9 9 9 9 0 0 9 9 9
            //    9 9 9 0 0 0 0 9 9 9
            //    9 9 9 1 0 0 2 9 9 9
            //    9 9 9 9 1 2 9 9 9 9
            //    9 9 9 9 9 9 9 9 9 9
            //    // Level 001
            //    9 9 9 9 9 9 9 9 9 9
            //    9 9 9 9 9 9 9 9 9 9
            // ...
            string inputLine;
            for( int i=0; i<5; i++) {
                getline(inputFileStream, inputLine);
            }
            
            // Now read each of the 118 (MaxNumberOfBoards) boards.  Each one starts with a comment that has the board number.
            for( int boardIndex = 0; boardIndex < MaxNumberOfBoards; boardIndex++) {
                // Read the comment with the board number
                getline(inputFileStream, inputLine);
                
                // For each board now read the BoardRows * BoardColumns number of board values, as integers
                for( int row=0; row<BoardRows; row++) {
                    for( int col=0; col<BoardColumns; col++) {
                        inputFileStream >> allBoards[ boardIndex][ row * BoardColumns + col];
                    }
                    // Get rid of end-of-line character at the end of each board, so we can get a clean start on reading the
                    //   first line of the next board.
                    getline(inputFileStream, inputLine);
                }
            }//end for( int boardIndex=0...

            // Close the input file.
            inputFileStream.close();
        }//end AllBoards() constructor
    
        // Get and Set member functions
        Board getBoard( int boardIndex) {
            // Validate board index number
            if( boardIndex < 0 || boardIndex > MaxNumberOfBoards) {
                cout << "In getBoard() inside AllBoards class, boardIndex "
                     << boardIndex << " is out of range. Exiting..." << endl;
                exit( -1);
            }
            
            // Construct a Board from one of all the boards
            Board newBoard( boardIndex, allBoards[ boardIndex], levelParValues[ boardIndex]);
            return newBoard;
        }
    
        // Get the par value for this board
        int getParValue( int boardIndex) {
            int theParValue = -1;
            if( boardIndex < NumberOfPresetBoardParValues) {
                theParValue = levelParValues[ boardIndex];
            }
            else {
                theParValue = 15;      // Default for par values at the upper end of the levels
            }
            return theParValue;
        } // end getParValue()
    
    private:
        int par = 0;             // The number of moves it should take to solve this level
        int currentLevel = -1;   // Which board we are on
        int allBoards[ 118][ BoardRows * BoardColumns];   // Array to store all 118 8x10 boards
    
        // Par values for levels 0 through 59.  Default is 15 after that.
        const int levelParValues[ NumberOfPresetBoardParValues] =
            // 0   1   2   3   4   5   6   7   8   9
            { 4,  3, 14,  5,  6,  4,  4, 14,  5, 25,  //  0 -  9
             12, 17, 17,  8,  4, 12,  9,  8, 12,  8,  // 10 - 19
             10, 10, 16, 13, 20, 14, 10,  9, 12, 14,  // 20 - 29
             15, 13, 20,  8, 15, 10, 10, 11,  7, 23,  // 30 - 39
              8, 11, 16, 14, 12, 13, 13,  3, 35, 18,  // 40 - 49
             26, 10, 13, 18, 26, 12, 15,  5, 22, 15}; // 50 - 59
}; //end class allBoards
