//
//  main.cpp
//  TA Program3 Work Play
//
//  Created by Viktor Kirillov on 9/25/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>      // For file input
#include <vector>		// For dictionary vector
#include <iomanip>		// For setw()
#include <cctype>       // For tolower()

using namespace std;

void displayIdInfo() {
    cout << " \n"
         << "Program #3: Work Play  \n"
         << "Author: Dale Reed      \n"
         << "Lab: Tues 8am          \n"
         << "System:  Codio         \n"
         << " \n";
}

void readInWordsFromFile(int wordLength, vector<string> &dictionary) {
	ifstream inputFileStream;
    string inputWord, fileName = "dictionary.txt";

	inputFileStream.open( fileName.c_str() );
	    
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << fileName << "  Exiting..." << endl;
        exit( -1);
    }

	// Read all the words from the file, and display them
    while( inputFileStream >> inputWord) {
		inputWord[0] = tolower(inputWord[0]);
		if (inputWord.length() == wordLength)
			dictionary.push_back(inputWord);
    }
    
    inputFileStream.close();
}

long binarySearch(string searchWord, vector<string> &dictionary) {
    long low, mid, high;     // array indices for binary search
    long searchResult = -1;  // Stores index of word if search succeeded, else -1
    
    // Binary search for word
    low = 0;
    high = dictionary.size() - 1;
    while ( low <= high)  {
        mid = (low + high) / 2;
        // SearchResult negative value means word is to the left, positive value means
        // word is to the right, value of 0 means word was found
        searchResult = searchWord.compare( dictionary[ mid] );
        if (searchResult == 0)
            return mid;
        else if (searchResult < 0)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}

int main(int argc, const char * argv[]) {
	
	vector< string> dictionary;    		// Vector of dictionary words read in from file
    int lengthOfWordsToUse = 3;         // Default length of word to use in word transformation
    string startWord = "dog";           // The start word for transformation
    string endWord = "cat";             // The end word for transformation
    int menuOption = -1;                // User menu option selection
	int input1, input2;
	string strInput;

    displayIdInfo();
    srand(1);
	
	readInWordsFromFile(lengthOfWordsToUse, dictionary);

    while(true) {
		cout << "Currently we have " << dictionary.size() << " words of length "
             << lengthOfWordsToUse << " in the dictionary.  \n"
             << "Changing from '" << startWord << "' to '" << endWord << "'" << endl
             << endl;
        
        cout << "Choose from the following options:  \n"
             << "   1. Change the word length        \n"
             << "   2. Display some dictionary words \n"
             << "   3. Get start and end words       \n"
             << "   4. Play the word change game     \n"
             << "   5. Find the end word with debug  \n"
             << "   6. Find the end word             \n"
             << "   7. Display an answer sequence    \n"
             << "   8. Exit the program              \n"
             << "Your choice -> ";
        cin >> menuOption;
        
		switch (menuOption) {
			case 1:
				cout << "\nWhat length words do you want to use? ";
				cin >> lengthOfWordsToUse;
				dictionary.clear();
				readInWordsFromFile(lengthOfWordsToUse, dictionary);
				break;
				
			case 2:
				cout << "\nEnter the start and end index values of words to display: ";
				cin >> input1 >> input2;
				for (int i=input1; i<=input2; i++)
					cout << "\t" << i << " " << dictionary[i] << endl;
				break;
				
			case 3:
				cout << "\nEnter starting word, or 'r' for a random word: ";
				cin.ignore();
				getline(cin, strInput);
				if (strInput == "r")
					startWord = dictionary[ rand()%dictionary.size() ];
				else {
					if (strInput.size() == lengthOfWordsToUse)
						startWord = strInput;
				}

				break;
				
			default:
				break;
		}
        
		cout << endl;
    }
	
	return 0;
}
