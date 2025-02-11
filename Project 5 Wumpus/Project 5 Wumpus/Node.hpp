//
//  Node.hpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 7/30/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <array>

class Node;
using Nodes = std::array<Node*, 3>;

class Node {
private:
    Nodes adjacent;
    int m_neighbors[3];
    int number;

public:
    void setAdjacents(Node &n0, Node &n1, Node &n2);
    void setAdjacents(int n0, int n1, int n2);
    Nodes& getAdjacents();
    int* getNeighbors();
    
    void setNumber(int n);
    int getNumber();
};

#endif /* Node_hpp */
