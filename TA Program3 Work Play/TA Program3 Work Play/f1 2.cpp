/* ------------------------------------------------
 * sample.cpp
 *
 * Class: Program #3 for CS 141, Fall 2019
 * System: Codio
 * Author: Dale Reed
 *
*/
#include <iostream>
#include <string>
#include <fstream>      // For file input
#include <vector>		// For dictionary vector
#include <iomanip>		// For setw()
#include <cctype>       // For tolower()
using namespace std;


//---------------------------------------------------------------
// Display ID info
//
void displayIdInfo()
{
    cout << " \n"
         << "Program #3: Work Play  \n"
         << "Author: Dale Reed      \n"
         << "Lab: Tues 8am          \n"
         << "System:  Codio         \n"
         << " \n";
}//end displayIDInfo()


void readInWordsFromFile()
{
	ifstream inputFileStream;
	
    string fileName = "dictionary.txt";
    string inputWord;

	// Open input file
	inputFileStream.open( fileName.c_str() );
	    
    // Verify that the open worked
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file " << fileName << "  Exiting..." << endl;
        exit( -1);
    }

	// Read all the words from the file, and display them
    while( inputFileStream >> inputWord) {
        cout << inputWord;
    }
    
    inputFileStream.close();
}


//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary vector, returning
// the word's index if found, -1 otherwise.
//
long binarySearch(
            string searchWord,            // word to be looked up
            vector< string> dictionary)   // the dictionary of words
{
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
        if ( searchResult == 0)  {
            // Word IS in dictionary, so return the index where the word was found
            return mid;
        }
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located before the mid location
        }
        else  {
            low = mid + 1; // word should be located after the mid location
        }
    }
    
    // Word was not found
    return -1;
}//end binarySearch()



//-----------------------------------------------------------------------------------------
int main()
{
    vector< string> dictionary;
	
    int lengthOfWordsToUse = 3;
	string startWord = "dog";
    string endWord = "cat";
    int menuOption = -1;

    ...

    // Menu display and handling infinite loop
    do {
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
				// Option 1 code
				break;
				
			case 2:
				// Option 2 code
				break;
				
			...
				
			default:
				break;
		}
        
    } while( true);
	
    return 0;
}//end main()


