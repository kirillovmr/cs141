/* ------------------------------------------------
 sample.cpp
 
 This is a sample program to illustrate the programming concepts needed to write
 the first program. Note that to run this code you would need to copy and paste
 it into main.cpp and run it from there.
 
 */

#include <iostream>   // For cin and cout
#include <cstdlib>    // For system("clear") used to clear the screen
#include <chrono>     // Used in pausing for some milliseconds using sleep_for(...)
#include <thread>     // Used in pausing for some milliseconds using sleep_for(...)
using namespace std;

//---------------------------------------------------------------------------
//  Main loop
int main() {
    char userInputCharacter;   // User input for some character
    
    cout << endl
    << "Go Flames! Choose from among the following options: \n"
    << "   1. Display U I C as horizontal block letters\n"
    << "   2. Display U I C as vertical block letters\n"
    << "   3. Display U I C as an animation\n"
    << "   4. Exit the program\n"
    << "Your choice -> ";
    cin >> userInputCharacter;
    cout << endl;
    
    // Handle the "Exit" option
    if( userInputCharacter == '4') {
        exit( -1);
    }
    
    // Display UIC
    else if( userInputCharacter == '1') {
        cout << "------------------------\n\n"
        << "*     *  ****     * *\n"
        << "*     *   **    *\n"
        << "*     *   **   *\n"
        << "*     *   **   *\n"
        << "*     *   **    *\n"
        << "  * *    ****     * *\n\n"
        << "------------------------" << endl;
    }
    
    else if (userInputCharacter == '2') {
        cout << "-------\n\n"
        << "*     *\n"
        << "*     *\n"
        << "*     *\n"
        << "*     *\n"
        << "*     *\n"
        << "  * *\n\n"
        << " ****\n"
        << "  **\n"
        << "  **\n"
        << "  **\n"
        << "  **\n"
        << " ****\n\n"
        << "   * *\n"
        << " *\n"
        << "*\n"
        << "*\n"
        << " *\n"
        << "   * *\n\n"
        << "-------" << endl;
    }
    
    // Display UIC as an animation
    else if( userInputCharacter == '3') {
        bool clearScreen = false;
        int letterSets, blanks;
        
        cout << "Clear the screen between displays? (Y/N) -> ";
        cin >> userInputCharacter;
        if (userInputCharacter == 'y') {
            clearScreen = true;
        }
        
        cout << "How many sets of letters? -> ";
        cin >> letterSets;
        cout << "How many blanks between letters (0..30)? -> ";
        cin >> blanks;
        
        for (int frame=0; frame<letterSets; frame++) {
            
            for (int j=0; j<(19+blanks*2); j++) cout << "-"; cout << endl;
            
            if (frame % 4 == 0) {
                // Display one set of letters, going through and printing one "slice" of each letter at a time.
                for( int i=0; i<9; i++) {
                    if(      i==0) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "  * *  "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    cout << endl;
                }//end for( int i...)
            }
            else if (frame % 4 == 1) {
                // Display one set of letters, going through and printing one "slice" of each letter at a time.
                for( int i=0; i<9; i++) {
                    if(      i==0) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "  * *  "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    cout << endl;
                }//end for( int i...)
            }
            else if (frame % 4 == 2) {
                // Display one set of letters, going through and printing one "slice" of each letter at a time.
                for( int i=0; i<9; i++) {
                    if(      i==0) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "  * *  "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << " *      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    cout << endl;
                }//end for( int i...)
            }
            else if (frame % 4 == 3) {
                // Display one set of letters, going through and printing one "slice" of each letter at a time.
                for( int i=0; i<9; i++) {
                    if(      i==0) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << "*     *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "  * *  "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << " ** "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "****"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "    "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    if(      i==0) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==1) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==2) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==3) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==4) { cout    << "*      "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==5) { cout    << " *     "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==6) { cout    << "    * *"; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==7) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    else if( i==8) { cout    << "       "; for(int j=0; j<blanks; j++) cout << " "; }
                    
                    cout << endl;
                }//end for( int i...)
            }
            
            for (int j=0; j<(19+blanks*2); j++) cout << "-"; cout << endl;
            
            // Clear the screen after the letters are displayed.
            if (clearScreen) {
                this_thread::sleep_for(chrono::milliseconds( 185));    // Sleep for 185 milliseconds
                system("clear");
            }
        }
        
    }//end else if( userInputCharacter == '2' ...
    
    return 0;
}//end main()
