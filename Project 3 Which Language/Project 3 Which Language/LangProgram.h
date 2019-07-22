//
//  LangProgram.h
//  Project 3 Which Language
//
//  Created by Viktor Kirillov on 7/9/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef LangProgram_h
#define LangProgram_h

#include <iostream>
#include <string>
#include <iomanip>      // For setw
//#include <cmath>

#include "FileReader.h"

using namespace std;

class LangProgram {
private:
    string *m_fileNames; // Will store array of .txt filenames
    string *m_languageNames = new string[NUM_FILES+1]; // Will store name of languages + "USER"
    int **m_languages = new int*[NUM_FILES]; // Will store 2D array of all parsed Languages -> num of letters
    FileReader m_fr;
    
    void parseFiles() {
        // Creating, initializing and Filling 2D Array
        for (int i=0; i<NUM_FILES; i++) {
            m_languages[i] = new int[LIMIT];
            m_languages[i] = m_fr.parseFile(m_fileNames[i]);
        }
    }
    
    void extractLanguageNames() {
        for (int i=0; i<NUM_FILES; i++)
            m_languageNames[i] = m_fileNames[i].substr(7, 4);
        m_languageNames[NUM_FILES] = "USER";
    }
    
    void displayHeader(bool tab=false, bool userColumn=false) {
        if (tab)
            cout << "\t";
        int columns = userColumn ? NUM_FILES + 1 : NUM_FILES;
        for (int i=0; i<columns; i++)
            cout << setw(6) << m_languageNames[i];
        cout << endl;
    }
    
    // Displaying characters count
    void displayData(int **data) {
        for (int r=0; r<LIMIT; r++) {
            cout << (char)(r+65) << ":\t";
            for (int i=0; i<NUM_FILES; i++)
                cout << setw(6) << data[i][r];
            cout << endl;
        }
        cout << endl;
    }
    
    // Displaying alphabet
    void displayData(char **data, bool userColumn=false) {
        int columns = userColumn ? NUM_FILES + 1 : NUM_FILES;
        for (int r=0; r<LIMIT; r++) {
            for (int i=0; i<columns; i++)
                cout << setw(6) << data[i][r];
            cout << endl;
        }
        cout << endl;
    }
    
    // For Stage 3
    void displayLetterCountInLine(int *numLetters) {
        cout << endl;
        for (int i=0; i<LIMIT; i++) {
            cout << (char)(i+65) << ":" << numLetters[i] << " ";
        }
        cout << endl << endl;
    }
    
    // Stage 1
    void displayLetterFrequencyCounts() {
        cout << "Letter Frequency Counts:\n";
        displayHeader(true);
        displayData(m_languages);
    }
    
    // Stage 2
    char *selectionSort(int arr[LIMIT]) {
        int *sorted = new int[LIMIT];
        char *alphabet = new char[LIMIT];
        
        // Copying array
        for (int i=0; i<LIMIT; i++) {
            sorted[i] = arr[i];
            alphabet[i] = (char)(65+i);
        }
        
        // Sorting
        int j, min, temp;
        for (int i=0; i <LIMIT-1; i++) {
            min = i;
            for (j=i+1; j<LIMIT; j++)
                if (sorted[j] > sorted[min])
                    min = j;
            temp = sorted[i];
            sorted[i] = sorted[min];
            sorted[min] = temp;
            
            temp = alphabet[i];
            alphabet[i] = alphabet[min];
            alphabet[min] = temp;
        }
        return alphabet;
    }
    
    void displayLetterFrequencyOrder(int userText[LIMIT] = {}) {
        char **sortedAlphabet = new char*[userText ? NUM_FILES + 1 : NUM_FILES];
        
        // Initializing and filling 2D array with sorder letter frequency
        for (int i=0; i<NUM_FILES; i++) {
            sortedAlphabet[i] = new char[LIMIT];
            sortedAlphabet[i] = selectionSort(m_languages[i]);
        }
        
        // Initializing anf filling an array with sorted user input letter frequency
        if (userText) {
            sortedAlphabet[NUM_FILES] = new char[LIMIT];
            sortedAlphabet[NUM_FILES] = selectionSort(userText);
        }
        
        cout << "Letter frequency order:\n";
        if (userText) {
            displayHeader(false, true);
            displayData(sortedAlphabet, true);
        }
        else {
            displayHeader();
            displayData(sortedAlphabet);
        }
    }
    
    // Stage 3
    int* userInput() {
        string input;
        cout << "Copy and paste a paragraph of text to be analyzed, followed by ^z (PC) or ^d (Mac):\n";
        cin.ignore();
        getline(cin, input, '\n');
        
        // In order not to change "countInputChars.cpp", users input goes in file
        string fileName = m_fr.stringToFile(input);
        
        int *parsedText = new int[LIMIT];
        parsedText = m_fr.parseFile(fileName);
        
        displayLetterCountInLine(parsedText);
        displayLetterFrequencyOrder(parsedText);
        return parsedText;
    }
    
    // Stage 4: Calculating Mean Squared Error for each language
    // This stage is messy and NOT optimized coz i was testing a lot with different approaches.
    // But it works, at least for the given task and test cases.
    void detectLanguage(int *parsedInput) {
        double *MSE = new double[NUM_FILES + 1];
        double difference;
        
        // Translate number of characters into percentage
        double **languages_percentage = new double*[NUM_FILES];
        
        // Going through each language
        for (int i=0; i<NUM_FILES; i++) {
            languages_percentage[i] = new double[LIMIT];
            
            int total_letters_in_lang = 0;
            
            // Count total number of characters
            for (int j=0; j<LIMIT; j++)
                total_letters_in_lang += m_languages[i][j];
            
            // Count % of characters by amount
            for (int j=0; j<LIMIT; j++)
                languages_percentage[i][j] = static_cast<double>(m_languages[i][j]) / total_letters_in_lang;
        }
        
        // Count percentage for user input
        double *input_percentage = new double[LIMIT];
        int total_letters_in_input = 0;
        
        for (int i=0; i<LIMIT; i++)
            total_letters_in_input += parsedInput[i];
        
        for (int i=0; i<LIMIT; i++)
            input_percentage[i] = static_cast<double>(parsedInput[i]) / total_letters_in_input;
        

        // The better way is to count MSE from percentages.
        for (int i=0; i<NUM_FILES; i++) {
            MSE[i] = 0;
            for (int j=0; j<LIMIT; j++) {
                difference = languages_percentage[i][j] - input_percentage[j];
                MSE[i] += difference * difference;
            }
            cout << "MSE for " << m_languageNames[i] << ": " << MSE[i] << endl;
        }
        
        // Find the least MSE
        int leastMSEindex = 0;
        for (int i=1; i<NUM_FILES; i++)
            if (MSE[i] < MSE[leastMSEindex])
                leastMSEindex = i;
        
        cout << "Language is " << m_languageNames[leastMSEindex] << endl;
    }
    
public:
    LangProgram(string fileNames[NUM_FILES]) {
        m_fileNames = fileNames;
        extractLanguageNames();
        parseFiles();
    }
    
    void loop() {
        short int input;
        int *parsedInput = new int[LIMIT];
        
        cout << "Program 3: Which Language.\n\n"
        << "Select from the following stages of output to display:\n"
        << "\t1. Letter frequency counts.\n"
        << "\t2. Letter frequency order.\n"
        << "\t3. Get user input and display frequency counts.\n"
        << "\t4. Get user input, display frequency counts, and display language.\n"
        << "\t0. Exit the program\n"
        << "Your choice --> ";
        cin >> input;
        cout << endl;
        
        switch (input) {
            case 1:
                displayLetterFrequencyCounts();
                break;
            case 2:
                displayLetterFrequencyCounts();
                displayLetterFrequencyOrder();
                break;
            case 3:
                displayLetterFrequencyCounts();
                displayLetterFrequencyOrder();
                userInput();
                break;
            case 4:
                parsedInput = userInput();
                detectLanguage(parsedInput);
                break;
            default:
                break;
        }
    }
};

#endif /* LangProgram_h */
