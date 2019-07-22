//
//  Decoder.hpp
//  Project 4 Decode
//
//  Created by Viktor Kirillov on 7/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Decoder_hpp
#define Decoder_hpp

#include <string>
#include "Pipeline.hpp"

class Decoder {
public:
    static int **m_vigenereTable;
    
    static int m_transposition;
    static std::string m_secret;
    
    // Instance of pipeline
    Pipeline m_pl;
    
    // Adds transposition parameter for Ceasar cipher
    void setTransposition(int transposition);
    
    // Adds secret parameter for Vigenere cipher
    void setSecret(std::string secret);
    
    // Adds function to pipeline
    void addPipe(std::string (*function)(std::string));
    
    // Removes all functions from pipeline
    void clear();
    
    // Overloading call operator
    std::string operator()(std::string customString);
    
    
    // Prints a string
    static std::string printString(std::string originalStr);
    
    // Returns a string with reverced words
    static std::string wordRevercer(std::string originalStr);
    
    // Returns a string encoded with caesar cipher
    static std::string caesarCipherPipe(std::string originalStr);
    
    // Returns a string encoded with vigenere cipher
    static std::string vigenereCipherPipe(std::string originalStr);
    static std::string vigenereCipherDecoderPipe(std::string originalStr);
    
    // Generates Vigenere table
    static void vigenereTableGenerator();
    
    // Prints Vinegare Table
    static void _printVigenereTable();
    
    // Returns required length keyword same length as originalString
    static std::string _generateFullKeyword(std::string originalStr, std::string keyword);
};

#endif /* Decoder_hpp */
