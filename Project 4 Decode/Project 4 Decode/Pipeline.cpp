//
//  Pipeline.cpp
//  Project 4 Decode
//
//  Created by Viktor Kirillov on 7/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Pipeline.hpp"

std::string Pipeline::operator()(std::string customString) {
    for (int i=0; i<m_pipes.size(); i++)
        customString = m_pipes[i](customString);
    return customString;
}

void Pipeline::addPipe(std::string (*function)(std::string)) {
    pFunc func = function;
    m_pipes.push_back(func);
}

void Pipeline::clear() {
    m_pipes.clear();
}
