//
//  Program.cpp
//  Project 4 Decode
//
//  Created by Viktor Kirillov on 7/18/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Program.hpp"
#include "Decoder.hpp"

using namespace std;

// Constructor bby default
Program::Program() {
    loop();
}

int Program::binaryDictionaryHits(std::string originalStr, std::vector<std::string> &dictionary) {
    int dicLen = static_cast<int>(dictionary.size());
    int hits = 0, middle, first, last;
    istringstream iss(originalStr);
    vector<string> strWords;
    string filename, word;
    bool found;
    
    // User string by words into vector
    while (iss >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        strWords.push_back(word);
    }
    
    // Binary search for word in dictionary
    for (string userWord: strWords) {
        first = 0; last = dicLen-1;
        found = false;
        
        while(first<=last && !found) {
            middle=(first+last)/2;

            if(dictionary[middle]==userWord) {
                found=true;
                hits += 1;
            }
            else {
                if(dictionary[middle]>userWord)
                    last=middle-1;
                else
                    first=middle+1;
            }
        }
    }
    
    return hits;
}

// Parses a filename, returns a vector of all words from file
std::vector<std::string> Program::parseWords(std::string filename, bool checkDuplicates) {
    vector<string> words;
    string word, alphaWord;
    fstream file;
    
    file.open(filename.c_str());
    
    while (file >> word) {
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        alphaWord = "";
        
        // Clearing word from punctuation
        for (char const letter: word)
            if (letter!='.' && letter!=',' && letter!=':' && letter!='(' && letter!=')' && letter!='_' && letter!='*' && letter!='"')
                alphaWord += letter;
            
        if (alphaWord.size() > 0) {
            // Looking for this word in words
            if (checkDuplicates) {
                if ( !(std::find(words.begin(), words.end(), alphaWord) != words.end()))
                    words.push_back(alphaWord);
            }
            else {
                 words.push_back(alphaWord);
            }
        }
        
    }
    
    return words;
}

std::string Program::decode(std::string &userInput, std::vector<std::string> &keys, std::vector<std::string> &dictionary) {
    struct bestHit {
        std::string key, direction, result;
        int transposition, hits=0;
    } bestHit;
    
    Decoder dr;
    
    // Going through each word for Vigenere cypher
    for (std::string keyword: keys) {
        for (int transposition=0; transposition<26; transposition++) {
            for (int reverce=0; reverce<2; reverce++) {
                dr.setTransposition(transposition);
                dr.setSecret(keyword);
                dr.addPipe(Decoder::vigenereCipherDecoderPipe);
                dr.addPipe(Decoder::caesarCipherPipe);
                if (reverce)
                    dr.addPipe(Decoder::wordRevercer);
                
                std::string res = dr(userInput);
                int hits = Program::binaryDictionaryHits(res, dictionary);
                if (hits > bestHit.hits) {
                    bestHit.hits = hits;
                    bestHit.transposition = transposition;
                    bestHit.direction = reverce ? "Reverse" : "Forwards";
                    bestHit.key = keyword;
                    bestHit.result = res;
                    
                    cout << "New best case. Dictionary hits: " << hits << ", keyword: " << keyword
                    << ", transposition: " << transposition << ", direction: " << bestHit.direction << endl;
                    cout << res << endl << endl;
                }
                dr.clear();
            }
        }
    }
    
    return bestHit.result;
}

// Program enter point
void Program::loop() {
    int input;
    cout << "Author: Viktor Kirillov" << endl
        << "Program 4: Decode" << endl
        << "TA: Hasti Sharifi" << endl
        << "JUL 20, 2019" << endl << endl
        << "Choose from the following options:" << endl
        << "1. Encode some text" << endl
        << "2. Decode using user-entered values" << endl
        << "3. Decode the ciphertext given with the assignment" << endl
        << "4. Exit program" << endl
        << "Your choice: ";
    cin >> input; cin.ignore();
    cout << endl;
    
    switch (input) {
        case 1:
            stage1();
            break;
        case 2:
            stage2();
            break;
        case 3:
            stage3();
            break;
        case 4:
            exit(4);
    }
}

void Program::stage1() {
    string userInput, direction, keyword;
    int transposition;
    
    cout << "Enter the text to be encoded: ";
    getline(cin, userInput);
    cout << "Enter direction (Forward or Reverse): ";
    getline(cin, direction);
    cout << "Enter transposition value (0..25): ";
    cin >> transposition; cin.ignore();
    cout << "Enter a keyword for Vigenere encryption: ";
    getline(cin, keyword);
    cout << "Keyword is: " << keyword << endl << endl;
    
    Decoder dr;
    dr.setTransposition(transposition);
    dr.setSecret(keyword);
    
    if (direction == "Reverse" || direction == "reverse")
        dr.addPipe(Decoder::wordRevercer);
    dr.addPipe(Decoder::caesarCipherPipe);
    dr.addPipe(Decoder::vigenereCipherPipe);
    
    cout << "Keyword, plainText and ciphertext are:" << endl
        << Decoder::_generateFullKeyword(userInput, keyword) << endl
        << userInput << endl
        << dr(userInput) << endl;
}

void Program::stage2() {
    vector<string> keys, dictionary = Program::parseWords("dictionary.txt");
    string userInput, possibleKeywords, keyword, filename, result;
    
    cout << "Enter the cipherText to be decoded: ";
    getline(cin, userInput);
    cout << "Enter the Vigenere keywords to be tried: ";
    getline(cin, possibleKeywords);
    cout << endl;
    
    // User input keys string to vector
    istringstream iss(possibleKeywords);
    while(iss >> keyword)
        keys.push_back(keyword);
    
    result = Program::decode(userInput, keys, dictionary);
    
    cout << "Decrypted text is:" << endl << result << endl << endl;
}

void Program::stage3() {
    vector<string> keys, dictionary = Program::parseWords("dictionary.txt");
    string userInput, filename, result;
    
    cout << "Ciphertext is: ";
    getline(cin, userInput);
    cout << "String of possible keywords taken from file: ";
    getline(cin, filename);
    cout << endl;
    
    keys = Program::parseWords(filename, true);
    
    result = Program::decode(userInput, keys, dictionary);
    
    cout << "Decrypted text is:" << endl << result << endl << endl;
}
