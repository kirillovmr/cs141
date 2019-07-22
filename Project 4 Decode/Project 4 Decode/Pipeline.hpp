//
//  Pipeline.hpp
//  Project 4 Decode
//
//  Created by Viktor Kirillov on 7/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Pipeline_hpp
#define Pipeline_hpp

#include <vector>
#include <string>

class Pipeline {
public:
    typedef std::string(*pFunc)(std::string);
    std::vector<pFunc> m_pipes;
    
    // Overloading call operator
    std::string operator()(std::string customString);
    
    // Adds function to pipeline
    void addPipe(std::string (*function)(std::string));
    
    // Removes all functions from pipeline
    void clear();
};

#endif /* Pipeline_hpp */
