/* -----------------------------------------------------------
 Project 2 Mastermind
 
 Class: CS 141, Summer 2019. T,Tr 1pm lab
 System: MacOS, Xcode 10
 Author: Viktor Kirillov
 
 -----------------------------------------------------------
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Game {
private:
    bool m_debug;
    unsigned short int m_values[3] = {0,0,0};
    unsigned short int m_maxSteps = 10;
    
    // Generate random, not repeating values
    void generateRandom() {
        unsigned short int nums[10] = {0,1,2,3,4,5,6,7,8,9};
        
        for (unsigned short int i=0; i<3; i++) {
            // Generating random index in range from 0 to 9-i
            unsigned short int index = rand() % (10-i);
            m_values[i] = nums[index];
            
            // Swapping values in nums
            if (i < 2) {
                nums[9-i] += nums[index];
                nums[index] = nums[9-i] - nums[index];
                nums[9-i] -= nums[index];
            }
        }
        if (m_debug) { displayHint(); }
    }
    
    // Gets input from user
    void getInput() {
        char input[3];
        cout << "\n\t\t\t\t\tIn place\tOut of place\n"
               << "\t\t\t\t\t--------\t------------\n";
        
        for (short int i=0; i<10; i++) {
            cout << i+1 << ". Your guess: ";
            cin >> input;
            
            if (atoi(input) <= 999) {
                // Handling game controls input
                switch (atoi(input)) {
                    case 0:
                        displayHint();
                        continue;
                    case 999:
                        endGame();
                        break;
                }
                
                unsigned short int* stats = checkInput(atoi(input));
                cout << "\tYou entered: " << input << "\t" << stats[0] << "\t\t\t " << stats[1] << endl;
                if (stats[0] == 3) {
                    cout << "*** Congratulations! ***\n" << "Exiting program...\n";
                    exit(0);
                }
            } else {
                i--;
            }
        }
        
        // Player exceeds number of tries
        endGame();
    }
    
    // Checks user input for In place and Out of place
    unsigned short int* checkInput(unsigned short int input) {
        unsigned short int* stats = new unsigned short int[2]; // stats[0] - In place, stats[1] - Out of place
        
        // Parsing integer input into array of numbers [0-9]
        unsigned short int inputArray[3] = {static_cast<unsigned short>(input/100),
            static_cast<unsigned short>(input%100/10), static_cast<unsigned short>(input%10)};
        
        for (int i=0; i<3; i++) {
            // Checking for [In place]
            if (inputArray[i] == m_values[i]) {
                stats[0] ? stats[0]++ : stats[0] = 1;
            }
            // Checking for [Out of place]
            else {
                for (int j=0; j<3; j++) {
                    if (inputArray[i] == m_values[j]) { stats[1] ? stats[1]++ : stats[1] = 1; }
                }
            }
        }
        return stats;
    }
    
    // Displays hint to the user of what computer selected
    void displayHint() {
        cout << "Computer selected [" << m_values[0] << ", "
            << m_values[1] << ", " << m_values[2] << "].\n";
    }
    
    void endGame() {
        cout << "Better luck next time.\n" << "Exiting program...\n";
        exit(0);
    }
    
public:
    Game(bool debug=false) {
        m_debug = debug;
        cout << "Project 2 Mastermind\n"
             << "Class: CS 141, Summer 2019. T,Tr 1pm lab\n"
             << "System: MacOS, Xcode 10\n"
             << "Author: Viktor Kirillov\n\n";
        
        cout << "The program selects 3 distinct random digits 0..9.\n"
             << "On each turn you guess 3 digits. The program indicates\n"
             << "how many are correct. You have 10 moves to guess the number.\n"
             << "Input of 000 displays the hidden digits. Input of 999 exits the program.\n"
             << "Good luck!\n\n";
    };
    
    void start() {
        this->generateRandom();
        this->getInput();
    }
};

int main(int argc, const char * argv[]) {
    
    srand(time(0));
    
    // Pass 0 or 1 into game() in order to witch on/off Debug mode
    Game game(1);
    game.start();
    
    return 0;
}
