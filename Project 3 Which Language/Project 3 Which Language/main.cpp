/* -----------------------------------------------------------
 Project 3 Which Language
 
 Class: CS 141, Summer 2019. T,Tr 1pm lab
 System: MacOS, Xcode 10
 Author: Viktor Kirillov
 
 -----------------------------------------------------------
 */

#include "LangProgram.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    string fileNames[NUM_FILES] = {"MacbethEnglish.txt", "MacbethFinnish.txt", "MacbethFrench.txt", "MacbethGerman.txt", "MacbethHungarian.txt", "MacbethItalian.txt", "MacbethPortuguese.txt", "MacbethSpanish.txt"};
    
    LangProgram lp(fileNames);
    lp.loop();
    
    return 0;
}
