//
//  Program.hpp
//  Project 4 Decode
//
//  Created by Viktor Kirillov on 7/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <vector>

class Program {
public:
    Program();
    
    // Check words occurence in dictionary, returns number of matches
    static int binaryDictionaryHits(std::string originalStr, std::vector<std::string> &dictionary);
    
    // Parses a filename, returns a vector of all words from file
    static std::vector<std::string> parseWords(std::string filename, bool checkDuplicates=false);
    
    // Basic pipeline creator and caller to decode text
    static std::string decode(std::string &userInput, std::vector<std::string> &keys, std::vector<std::string> &dictionary);
    
    void loop();

    void stage1();
    void stage2();
    void stage3();
};

#endif /* Program_hpp */
