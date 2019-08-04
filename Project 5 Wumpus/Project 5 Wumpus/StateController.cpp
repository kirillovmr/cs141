//
//  StateController.cpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 8/3/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "StateController.hpp"

void StateController::appendState(State state) {
    StateNode* node = new StateNode;
    node->pNext = m_pHead==nullptr ? nullptr : m_pHead;
    node->state = state;
    
    m_pHead = node;
    m_length += 1;
}

bool StateController::revertState() {
    if (m_length < 2)
        return false;
    
    m_pHead = m_pHead->pNext;
    m_length -= 1;
    
    return true;
}

State StateController::getState() {
    return m_pHead->state;
}

void StateController::eraseAll() {
    m_length = 0;
    m_pHead = nullptr;
}
