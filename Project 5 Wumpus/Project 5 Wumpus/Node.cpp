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

Nodes& Node::getAdjacents() {
    return adjacent;
}

void Node::setNumber(int n) {
    number = n;
}

int Node::getNumber() {
    return number;
}
