//
//  main.cpp
//  TA Program 2 Rally Songs
//
//  Created by Viktor Kirillov on 9/9/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <fstream>      // For file input
#include <cstdlib>      // For exit and abs

using namespace std;

// Global variables
int numberOfLinesToDisplay = 3;
ifstream inputFileStream;

int totalQuizTries = 0;
int totalQuizWins = 0;

// Functions to work with files
int readNumberOfLines(string filename) {
    
    // Open input file and verify that file was found
    inputFileStream.open( filename.c_str() );
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << filename << "  Exiting..." << endl;
        exit( -1);
    }
    
    // Read the number on the first line of the input file, which indicates how many subsequent
    // lines there are in the file.
    int numberOfLinesInFile = 0;
    inputFileStream >> numberOfLinesInFile;
    inputFileStream.close();
    
    return numberOfLinesInFile;
}

string getLineFromFile(string filename, int lineNumber) {
    
    // Open input file and verify that file was found
    inputFileStream.open( filename.c_str() );
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << filename << "  Exiting..." << endl;
        exit( -1);
    }
    
    string line;
    for (int i = 0; i <= lineNumber; i++) {
        getline(inputFileStream, line);
    }
    
    // Checking that line is not empty and not a title
    if (line.length() == 0)
        getline(inputFileStream, line);
    if (line[0] == '#')
        getline(inputFileStream, line);
    
    inputFileStream.close();
    return line;
}

// Functions that runs from main menu
void setNumberOfLines() {
    cout << "Enter the number of lines you want to display -> ";
    cin >> numberOfLinesToDisplay;
}

void getRandomFromCandidate(string candidateName) {
    int totalLines = readNumberOfLines(candidateName);
    int randomLineNumber;
    
    for (int i=0; i<numberOfLinesToDisplay; i++) {
        randomLineNumber = rand() % (totalLines - numberOfLinesToDisplay);
        cout << getLineFromFile(candidateName, randomLineNumber) << endl;
    }
}

void rallySongQuiz() {
    int randomCandidateNumber = (rand() % 2) + 1;
    int userGuess;
    
    if (randomCandidateNumber == 1)
        getRandomFromCandidate("Trump.txt");
    else
        getRandomFromCandidate("Warren.txt");
    
    cout << "\nEnter 1 for Trump, 2 for Warren: ";
    cin >> userGuess;
    
    totalQuizTries += 1;
    
    if (userGuess == randomCandidateNumber) {
        cout << "\nCorrect! ";
        totalQuizWins += 1;
    }
    else {
        cout << "\nWrong! ";
    }
    cout << "You got " << totalQuizWins << " out of " << totalQuizTries << ", which is " << (double)totalQuizWins / totalQuizTries * 100 << "%\n";
}

int main(int argc, const char * argv[]) {
    // Stores user input in main menu
    int userInput = 0;
    
    // Initialize the random number generator
    srand(1);
    
    // Loop for main menu
    while(userInput != 5) {
        cout << "---- Program 2: Political Lyrics ----\n"
            << "Select from the following:\n"
            << "1. Set number of lines to display\n"
            << "2. Get random lines from Trump.txt\n"
            << "3. Get random lines from Warren.txt\n"
            << "4. Rally song quiz\n"
            << "5. Exit the program\n"
            << "Your choice --> ";
        
        cin >> userInput;
        cout << "\n";
        
        if(userInput == 1)
            setNumberOfLines();
        else if (userInput == 2)
            getRandomFromCandidate("Trump.txt");
        else if (userInput == 3)
            getRandomFromCandidate("Warren.txt");
        else if (userInput == 4)
            rallySongQuiz();
        else if (userInput == 5)
            exit(-1);
        
        cout << endl;
    }
    
    return 0;
}
