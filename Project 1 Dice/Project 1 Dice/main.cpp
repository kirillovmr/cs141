/* -----------------------------------------------------------
 Project 1. Dice game
 
 Class: CS 141, Summer 2019. M,W 1pm lab
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
    short int score[2] = {0,0};
    short int turn = 0;
    short int sides[3][6] = {{1,4,4,4,4,4}, {2,2,2,5,5,5}, {6,3,3,3,3,3}}; // Red, Green, Blue appropriately
    char colors[2];
    
    // Converts letter color to integer
    short int colorToInt(char color) {
        return color == 'R' ? 0 : color == 'G' ? 1 : 2;
    };
    
    // Given user input, returns appropriate dice values
    int* getDiceValues(char *colors) {
        // Returning values of appropriate players
        int* values = new int[2];
        
        // Generating random numbers
        int nums[2] = {rand() % 6, rand() % 6};
        
        // Going through each player
        for (short int i=0; i<2; i++) {
            // Decoding color letter inco integer (0,1,2)
            short int color = this->colorToInt(colors[i]);
            
            // Selecting dice value for player
            values[i] = this->sides[color][nums[i]];
        }
        return values;
    };

public:
    Game() {
        cout << "Class: CS 141\n" << "System: C++ in codio.com\n" << "Welcome to the dice game, where you and your opponent each choose one of the red, green or blue dice and roll them.\n";
        cout << "The dice contain the following sides:\n" << "Red: 1 4 4 4 4 4\n";
        cout << "Green: 2 2 2 5 5 5\n" << "Blue: 6 3 3 3 3 3\n";
    };
    
    // Get user input (ex. 'RG', 'BG')
    void getInput() {
        cout << "Enter the die colors (R G or B):";
        cin >> this->colors;
    };
    
    // Game step
    void runDice(){
        int* values = this->getDiceValues(this->colors);
        
        // Updating state variables
        values[0] > values[1] ? this->score[0] ++ : this->score[1]++;
        this->turn++;
        
        cout << this->turn << ". " << colors[0] << ":" << values[0] << " " << colors[1] << ":" << values[1] << ", Score: " << score[0] << " to " << score[1] << endl;
    };
};

int main(int argc, const char * argv[]) {
    
    // Setting seed for rand()
    srand(time(0));
    
    Game game;
    game.getInput();
    
    for (short int i=0; i<50; i++) {
        game.runDice();
    }
    
    return 0;
}
