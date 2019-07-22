//
//  FileReader.h
//  Project 3 Which Language
//
//  Created by Viktor Kirillov on 7/9/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef FileReader_h
#define FileReader_h

#include <cctype>       // For the letter checking functions
#include <fstream>       // For file input
#include <cstdlib>      // For exit()

#define LIMIT 26        // Max array size, which is number of alphabet
#define NUM_FILES 8

using namespace std;

// Class-based implementation of countInputChars.cpp
class FileReader {
private:
public:
    string stringToFile(string input) {
        string fileName = "userInput.txt";
        ofstream file(fileName);
        if (file.is_open())
        {
            file << input;
            file.close();
        }
        else cout << "Unable to open file";
        
        return fileName;
    };
    
    int* parseFile(string fileName) {
        
        ifstream inputFileStream;  // declare the input file stream
        int *lettersArray = new int[LIMIT];  // count occurrences of characters
        char c = ' ';              // input character
        int i;                     // loop counter
        
        // open input file and verify
        inputFileStream.open(fileName.c_str());   // Convert C++ string to expected C-style string
        if( !inputFileStream.is_open()) {
            cout << "Could not find input file.  Exiting..." << endl;
            exit( -1);
        }
        
        // initialize lettersArray count values
        for (i=0; i<LIMIT; i++) {
            lettersArray[i] = 0;
        }
        
        // Process input one character at at time, echoing input
        // Note that the input skips leading spaces, which is why we don't see
        // them as part of the output.
        //        cout << "Reading characters from a file " << fileName << "..." << endl;
        while( inputFileStream >> c) {
            // convert alphabetic input characters to upper case
            if( isalpha( c)) {
                c = toupper( c);
                lettersArray[ c-'A']++; // update letter count, using the character as the index
                // cout << c << " ";    // Takes too long to display when enabled
            }
        }
        //        cout <<"\n";
        
        // display select portions of the table
        //        cout << "The alphabetic characters are: \n";
        for (i=0; i<LIMIT; i++) {
            // See if it is a printable character and if there were any of that character
            if ( lettersArray[ i] != 0 ) {
                // display the character and the number of occurences
                //                cout << (char)(i+'A') << ":" << setw(6) << lettersArray[ i] << "\n";
            }
        }
        //        cout <<"\n";       // newline
        
        inputFileStream.close();
        return lettersArray;
    }
};

#endif /* FileReader_h */
