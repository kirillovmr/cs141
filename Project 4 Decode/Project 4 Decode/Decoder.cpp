//
//  Decoder.cpp
//  Project 4 Decode
//
//  Created by Viktor Kirillov on 7/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Decoder.hpp"

int Decoder::m_transposition = 0;
void Decoder::setTransposition(int transposition) {
    m_transposition = transposition;
}

std::string Decoder::m_secret = " ";
void Decoder::setSecret(std::string secret) {
    m_secret = secret;
}

void Decoder::addPipe(std::string (*function)(std::string)) {
    m_pl.addPipe(function);
}

void Decoder::clear() {
    m_pl.clear();
}

std::string Decoder::operator()(std::string customString) {
    return m_pl(customString);
}


std::string Decoder::printString(std::string originalStr) {
    std::cout << originalStr << std::endl;
    return originalStr;
}

std::string Decoder::wordRevercer(std::string originalStr) {
    std::istringstream iss(originalStr);
    std::string word, newWord, newString;
    int j=0;
    
    // Going word by word in string
    while(iss >> word) {
        newWord = "";
        
        // Creating reverced word by going backwards in original word
        for (int i=static_cast<int>(word.length())-1; i>=0; i--)
            newWord += word[i];
        
        // Handling space before next word
        newWord = j>0 ? " " + newWord : newWord;
        newString.append(newWord);
        j++;
    }

    return newString;
}

std::string Decoder::caesarCipherPipe(std::string originalStr) {
    int transposition = m_transposition;
    std::string newString = "";
    
    // Going through each letter in string
    for(int i=0; i<static_cast<int>(originalStr.length()); i++) {
        int code = (int)originalStr[i];
        
        // Capital letter
        if ( code >= 65 && code <= 90 ) {
            code += transposition;
            newString += code>90 ? code-26 : code;
        }
        // Small letter
        else if ( code >= 97 && code <= 122 ) {
            code += transposition;
            newString += code>122 ? code-26 : code;
        }
        // Not an alpha
        else
            newString += originalStr[i];
    }
    return newString;
}

std::string Decoder::vigenereCipherPipe(std::string originalStr) {
    int lenOriginalStr = static_cast<int>(originalStr.length()), code;
    std::string keyword = m_secret, newString = "", fullKeyword;
    
    // Check is vigenereTable generated
    if (m_vigenereTable[0] == 0x0)
        vigenereTableGenerator();
    
    fullKeyword = _generateFullKeyword(originalStr, keyword);
    
    // fullKeyword to upper
    std::transform(fullKeyword.begin(), fullKeyword.end(), fullKeyword.begin(), ::toupper);
    
    // Applying Vigenere Cipher
    for (int i=0; i<lenOriginalStr; i++) {
        code = (int)originalStr[i];
        
        // Capital letter
        if ( code >= 65 && code <= 90 )
            newString += m_vigenereTable[(int)fullKeyword[i]-65][code-65];
        // Small letter
        else if ( code >= 97 && code <= 122 )
            newString += (char)((int)m_vigenereTable[(int)fullKeyword[i]-65][code-97] + 32);
        // Not an alpha
        else
            newString += originalStr[i];
    }
    
    return newString;
}

std::string Decoder::vigenereCipherDecoderPipe(std::string originalStr) {
    int lenOriginalStr = static_cast<int>(originalStr.length()), code, newCode;
    std::string keyword = m_secret, newString = "", fullKeyword;
    
    // Generating same-size keyword string
    fullKeyword = _generateFullKeyword(originalStr, keyword);
    
    // fullKeyword to upper
    std::transform(fullKeyword.begin(), fullKeyword.end(), fullKeyword.begin(), ::toupper);
    
    // Decoding Vigenere Cipher
    for (int i=0; i<lenOriginalStr; i++) {
        code = (int)originalStr[i];
        
        // Capital letter
        if ( code >= 65 && code <= 90 ) {
            newCode = (code-64) - ((int)fullKeyword[i]-64);
            newString += (char)(newCode<0 ? newCode+26+65 : newCode+65);
        }
        // Small letter
        else if ( code >= 97 && code <= 122 ) {
            newCode = (code-96) - ((int)fullKeyword[i]-64);
            newString += (char)(newCode<0 ? newCode+26+97 : newCode+97);
        }
        // Not an alpha
        else
            newString += originalStr[i];
    }
    
    return newString;
}

// Initializing array for vigenereTable
int **Decoder::m_vigenereTable = new int*[26];

void Decoder::vigenereTableGenerator() {
    // Initialization
    for (int i=0; i<26; i++)
        m_vigenereTable[i] = new int[26];
    
    // Filling with char codes
    for (int i=0; i<26; i++)
        for (int j=0; j<26; j++)
            m_vigenereTable[i][j] = 65+i+j<=90 ? 65+i+j : 65+i+j-26;
}

void Decoder::_printVigenereTable() {
    for (int i=0; i<26; i++, std::cout<<std::endl)
        for (int j=0; j<26; j++)
            std::cout << (char)m_vigenereTable[i][j] << " ";
}

std::string Decoder::_generateFullKeyword(std::string originalStr, std::string keyword) {
    int lenOriginalStr = static_cast<int>(originalStr.length()), lenKeyword = static_cast<int>(keyword.length());
    int repeatNTimes = ceil(static_cast<float>(lenOriginalStr) / static_cast<float>(lenKeyword));
    std::string fullKeyword = "";
    
    // Generating same-size keyword string
    for (int i=0; i<repeatNTimes; i++)
        fullKeyword += keyword;
    
    return fullKeyword;
}
