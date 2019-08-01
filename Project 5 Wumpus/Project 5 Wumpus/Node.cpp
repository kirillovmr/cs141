//
//  Node.cpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 7/30/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Node.hpp"

void Node::setAdjacents(Node &n0, Node &n1, Node &n2) {
    adjacent[0] = &n0;
    adjacent[1] = &n1;
    adjacent[2] = &n2;
}
void Node::setAdjacents(int n0, int n1, int n2) {
    m_neighbors[0] = n0;
    m_neighbors[1] = n1;
    m_neighbors[2] = n2;
}

Nodes& Node::getAdjacents() {
    return adjacent;
}
int* Node::getNeighbors() {
    return m_neighbors;
}

void Node::setNumber(int n) {
    number = n;
}

int Node::getNumber() {
    return number;
}
