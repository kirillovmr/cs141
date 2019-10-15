//
//  Board.cpp
//  TA Program 4 Vexed
//
//  Created by Viktor Kirillov on 10/14/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <vector>
#include "Board.hpp"

using namespace std;

Board::Board(){
    m_level = m_par = m_nonEmptyTiles = -1;
    for (int i = 0; i < BoardRows * BoardColumns; i++)
        m_board[i] = -1;
}

Board::Board(int boardNumber, int boardValues[BoardRows * BoardColumns], int par) {
    m_level = boardNumber;
    m_par = par;
    m_nonEmptyTiles = 0;
    for (int i = 0; i < BoardRows * BoardColumns; i++) {
        if (boardValues[i] != 0 && boardValues[i] != 9)
            m_nonEmptyTiles++;
        m_board[i] = boardValues[i];
    }
}

int Board::getNonEmptyTiles() {
    return m_nonEmptyTiles;
}

// Final version to display letters and indexes
//
void Board::displayBoard() {
    cout << "Board " << m_level << " with par " << m_par << " is: " << endl;
    
    // Top row of numbers
    cout << "    "; for (int i=0; i<BoardColumns; i++) { cout << i << " "; } cout << endl;
    
    // Top row of dashes
    cout << "  "; for (int i=0; i<BoardColumns*2+3; i++) { cout << "-"; }
    
    for (int i=0; i < BoardRows * BoardColumns; i++) {
        if (i % BoardColumns == 0)
            cout << endl << (char)(i/BoardColumns+65) << " | ";
        
        cout << m_boardChar[m_board[i]] << " ";
        
        if (i % BoardColumns == BoardColumns - 1)
            cout << "| " << (char)(i/BoardColumns+65);
    }
    cout << endl;
    
    // Bottom row of dashes
    cout << "  "; for (int i=0; i<BoardColumns*2+3; i++) { cout << "-"; } cout << endl;
    
    // Bottom row of numbers
    cout << "    "; for (int i=0; i<BoardColumns; i++) { cout << i << " "; } cout << endl;
    
    cout << endl;
}

// Second version to display the border and characters
//
//void Board::displayBoard() {
//    cout << "Board " << m_level << " with par " << m_par << " is: " << endl;
//    for (int i=0; i<BoardColumns*2+3; i++)
//        cout << "-";
//
//    for (int i=0; i < BoardRows * BoardColumns; i++) {
//        if (i % BoardColumns == 0)
//            cout << endl << "| ";
//
//        cout << m_boardChar[m_board[i]] << " ";
//
//        if (i % BoardColumns == BoardColumns - 1)
//            cout << "|";
//    }
//    cout << endl;
//
//    for (int i=0; i<BoardColumns*2+3; i++)
//        cout << "-";
//    cout << endl << endl;
//}

// First version to simply display board
//
//void Board::displayBoard() {
//    cout << "Board " << m_level << " with par " << m_par << " is: " << endl;
//    for (int i=0; i < BoardRows * BoardColumns; i++) {
//        if (i % BoardColumns == 0 && i > 0)
//            cout << endl;
//        cout << m_board[i] << " ";
//    }
//    cout << endl << endl;
//}

bool Board::move(int indexFrom, int indexTo) {
    vector<int> idxToFall, idxToExplode;
    
    if (indexFrom < 0 || indexTo < 0 || indexFrom >= BoardRows*BoardColumns || indexTo >= BoardRows*BoardColumns)
        return false;
    if (m_board[indexFrom] == 9) {
        cout << "Attempting to move a \"wall\" character '.'.  Please retry." << endl;
        return false;
    }
    if (m_board[indexTo] != 0) {
        cout << "Attempting to move into a non-empty space.  Please retry." << endl;
        return false;
    }
    
    // Moving the tile
    cout << "Moving " << indexFrom << " " << m_boardChar[ m_board[indexFrom]] << endl;
    m_board[indexTo] = m_board[indexFrom];
    m_board[indexFrom] = 0;
    
    // Queueing all upper cells to fall
    int i = indexFrom - BoardColumns;
    while(i > 0 && m_board[i] != 0 && m_board[i] != 9) {
        idxToFall.push_back(i);
        i -= BoardColumns;
    }
    
    // Queueing Moved cell to fall
    idxToFall.push_back(indexTo);
    
    // If there is something to fall
    while (idxToFall.size()) {
        
        // Making them fall
        for (auto j : idxToFall) {
            int indexAfterDrop = checkForDrop(j);
            idxToExplode.push_back(indexAfterDrop);
        }
        idxToFall.clear();
        
        // Cheking whether the cells that have just fallen need to be exploded
        for (auto j : idxToExplode) {
            destroyAdjacents(j, idxToFall);
        }
        idxToExplode.clear();
    }
    
    return true;
}

int Board::checkForDrop(int indexFrom) {
    int startIndex = indexFrom;
    if (m_board[indexFrom] == 0 || m_board[indexFrom] == 9)
        return indexFrom;
    
    int nextIndex = indexFrom + BoardColumns;
    if (nextIndex >= BoardRows*BoardColumns)
        return indexFrom;
    
    while (m_board[nextIndex] == 0) {
        m_board[nextIndex] = m_board[indexFrom];
        m_board[indexFrom] = 0;
        
        indexFrom = nextIndex;
        nextIndex = indexFrom + BoardColumns;
        if (nextIndex >= BoardRows*BoardColumns)
            break;
    }
    
    if(startIndex != indexFrom)
        cout << "Dropping " << indexFrom << " " << m_boardChar[ m_board[indexFrom]] << endl;
    
    return indexFrom;
}

bool Board::destroyAdjacents(int indexFrom, vector<int> &idxToFall) {
    vector<int> indexesToDestroy;
    indexesToDestroy.push_back(indexFrom);
    
    int i=0;
    while(i<indexesToDestroy.size()) {
        int index = indexesToDestroy[i];
        
        // If there is a column to the right
        if ( (index+1) % BoardColumns != 0  && index+1 < BoardRows*BoardColumns)
            // If next index holds same element
            if ( m_board[index+1] == m_board[indexFrom] )
                // If not yet in indexes
                if (find(indexesToDestroy.begin(), indexesToDestroy.end(), index+1) == indexesToDestroy.end())
                    indexesToDestroy.push_back(index+1);
        
        // Left
        if ( (index-1) % BoardColumns != BoardColumns-1  && index-1 > 0)
            if ( m_board[index-1] == m_board[indexFrom] )
                if (find(indexesToDestroy.begin(), indexesToDestroy.end(), index-1) == indexesToDestroy.end())
                    indexesToDestroy.push_back(index-1);
        
        // Top (Probably even not possible to have the same tile on top)
//        if ( (index-BoardColumns) > 0)
//            if ( m_board[index-BoardColumns] == m_board[indexFrom] )
//                if (find(indexesToDestroy.begin(), indexesToDestroy.end(), index-BoardColumns) == indexesToDestroy.end())
//                    indexesToDestroy.push_back(index-BoardColumns);
        
        // Bottom
        if ( (index+BoardColumns) < BoardRows*BoardColumns)
            if ( m_board[index+BoardColumns] == m_board[indexFrom] )
                if (find(indexesToDestroy.begin(), indexesToDestroy.end(), index+BoardColumns) == indexesToDestroy.end())
                    indexesToDestroy.push_back(index+BoardColumns);
        
        i++;
    }
    
    // Destroying
    if (indexesToDestroy.size() > 1) {
        for (auto idx : indexesToDestroy) {
            // Make sure that air is not gonna explode 😎
            if (m_board[idx] != 0 && m_board[idx] != 9) {
                m_board[idx] = 0;
                m_nonEmptyTiles--;
                cout << "Removed idx " << idx << endl;
                
                // Queueing elements above
                // If not wall above
                if (m_board[idx-BoardColumns] != 9 && m_board[idx-BoardColumns] != 0) {
                    int i = idx - BoardColumns;
                    while(i > 0 && m_board[i] != 0 && m_board[i] != 9) {
                        idxToFall.push_back(i);
                        i -= BoardColumns;
                    }
                }
            }
        }
    }
    return true;
}
