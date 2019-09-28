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

bool checkDiffByLetters(string word1, string word2) {
	if (word1 == word2)
		return false;
	
	if (word1.size() != word2.size())
		return false;
	
	int err=0;
	for (int i=0; i<word1.size(); i++) {
		if (word1[i] != word2[i])
			err += 1;
		
		if (err > 1)
			return false;
	}
	return true;
}

void playGame(string &startWord, string &endWord, vector<string> &dictionary) {
	int i = 1;
	string input, currentWord;
	currentWord = startWord;
	
	cin.ignore();
	while (currentWord != endWord) {
		cout << i << ". Previous word is '" << currentWord << "'. Next word: ";
		getline(cin, input);
		
		// Check input word
		if (input.length() == currentWord.length())
			if (binarySearch(input, dictionary) != -1)
				if (checkDiffByLetters(currentWord, input)) {
					currentWord = input;
					i += 1;
				}
	}
	cout << "Congratulations, you did it!" << endl;
}

bool existsInVector(string word, vector<string> &vect) {
	for (auto w : vect)
		if (w == word) {
			return true;
		}
	return false;
}

void findEndWord(string startWord, string endWord, vector<string> &dictionary, vector<string> &path, bool debug = false) {
	
	vector<string> stack, wordsSameSize;
	vector<unsigned long*> endPointsVec;
	stack.push_back(startWord);
	bool found = false;
	
	int i = 0;
	unsigned long startPoint, endPoint;
	
	while (i < stack.size()) {
		wordsSameSize.clear();
		
		startPoint = stack.size();
		
		if (debug) cout << i << ". " << stack[i] << ":\t";
		
		// Going through dictionary
		for (int j=0; j<dictionary.size(); j++)
			// Creating vector of words that work for us
			if (checkDiffByLetters(dictionary[j], stack[i]))
				wordsSameSize.push_back(dictionary[j]);
		
		// Going through list of words in order
		for (int k=0; k<wordsSameSize[0].size(); k++) { // k < size of word
			for (int j=0; j<wordsSameSize.size(); j++) { // going through vector
				if (wordsSameSize[j][k] != stack[i][k]) {
					if (!existsInVector(wordsSameSize[j], stack)) {
							
						stack.push_back(wordsSameSize[j]);
						if (debug) cout << stack.size()-1 << ":" << wordsSameSize[j] << " ";
						
						if (wordsSameSize[j] == endWord) {
							cout << "\n\nWinning sequence was found!" << endl;
							found = true;
						}
					}
				}
				if (found) break;
			}
			if (found) break;
		}
		
		endPoint = stack.size()-1;
//		unsigned long endPoints[2] = {startPoint, endPoint};
		unsigned long *endPoints = new unsigned long[2]{startPoint, endPoint};
		endPointsVec.push_back(endPoints);
		
		if (debug) cout << endl;
		i += 1;
		
		if (found) break;
	}
	
	int currentID = static_cast<int>(stack.size()-1);
	path.clear();
	path.push_back(to_string(currentID) + ". " + stack[currentID]);
	
	// Traversing vector back to find path
	for (int j=static_cast<int>(endPointsVec.size()-1); j>=0; j--) {
		if (currentID >= endPointsVec[j][0] && currentID <= endPointsVec[j][1]) {
			currentID = j;
			path.push_back(to_string(currentID) + ". " + stack[currentID]);
		}
	}
}

int main(int argc, const char * argv[]) {
	
	vector<string> dictionary, path;    		// Vector of dictionary words read in from file
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
				else
					if (strInput.size() == lengthOfWordsToUse)
						if (binarySearch(strInput, dictionary) != -1)
							startWord = strInput;
				
				cout << "\nEnter ending word, or 'r' for a random word: ";
				getline(cin, strInput);
				if (strInput == "r")
					endWord = dictionary[ rand()%dictionary.size() ];
				else
					if (strInput.size() == lengthOfWordsToUse)
						if (binarySearch(strInput, dictionary) != -1)
							endWord = strInput;
				break;
				
			case 4:
				playGame(startWord, endWord, dictionary);
				break;
				
			case 5:
				findEndWord(startWord, endWord, dictionary, path, true);
				break;
				
			case 6:
				findEndWord(startWord, endWord, dictionary, path);
				break;
				
			case 7:
				cout << endl;
				for (int i=0; i<path.size(); i++)
					cout << path[i] << endl;
				break;
				
			case 8:
				cout << "\nExiting the program\n";
				exit(0);
				
			default:
				break;
		}
        
		cout << endl;
    }
	
	return 0;
}
