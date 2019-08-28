//
//  Game.cpp
//  Project 5 Wumpus
//
//  Created by Viktor Kirillov on 7/30/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include <iostream>
#include <cstdlib> // rand, srand, atoi, exit
#include <vector>
#include <string>
#include <cctype> // tolower
#include <ctime>
#include "Game.hpp"

using namespace std;

Game::Game() {
    // Setting up room number
    for (int i=0; i<20; i++)
        m_rooms[i].setNumber(i+1);
    
    // Setting up room connections.
    // Since rooms are array of nodes, Room 6 is rooms[5] and so on.
    m_rooms[0].setAdjacents(m_rooms[1], m_rooms[4], m_rooms[7]);
    m_rooms[1].setAdjacents(m_rooms[0], m_rooms[2], m_rooms[9]);
    m_rooms[2].setAdjacents(m_rooms[1], m_rooms[3], m_rooms[11]);
    m_rooms[3].setAdjacents(m_rooms[2], m_rooms[4], m_rooms[13]);
    m_rooms[4].setAdjacents(m_rooms[0], m_rooms[3], m_rooms[5]);
    m_rooms[5].setAdjacents(m_rooms[4], m_rooms[6], m_rooms[14]);
    m_rooms[6].setAdjacents(m_rooms[5], m_rooms[7], m_rooms[16]);
    m_rooms[7].setAdjacents(m_rooms[0], m_rooms[6], m_rooms[8]);
    m_rooms[8].setAdjacents(m_rooms[7], m_rooms[9], m_rooms[17]);
    m_rooms[9].setAdjacents(m_rooms[1], m_rooms[8], m_rooms[10]);
    m_rooms[10].setAdjacents(m_rooms[9], m_rooms[11], m_rooms[18]);
    m_rooms[11].setAdjacents(m_rooms[2], m_rooms[10], m_rooms[12]);
    m_rooms[12].setAdjacents(m_rooms[11], m_rooms[13], m_rooms[19]);
    m_rooms[13].setAdjacents(m_rooms[3], m_rooms[12], m_rooms[14]);
    m_rooms[14].setAdjacents(m_rooms[5], m_rooms[13], m_rooms[15]);
    m_rooms[15].setAdjacents(m_rooms[14], m_rooms[16], m_rooms[19]);
    m_rooms[16].setAdjacents(m_rooms[6], m_rooms[15], m_rooms[17]);
    m_rooms[17].setAdjacents(m_rooms[8], m_rooms[16], m_rooms[18]);
    m_rooms[18].setAdjacents(m_rooms[10], m_rooms[17], m_rooms[19]);
    m_rooms[19].setAdjacents(m_rooms[12], m_rooms[15], m_rooms[18]);
}

int* Game::getRandomNonRepeatingNumbers(int rangeFrom, int rangeTo, int howMany) {
    int totalNum = rangeTo-rangeFrom;
    int numbers[totalNum];
    for (int i=0; i<totalNum; i++)
        numbers[i] = rangeFrom+i;
    
    srand(static_cast<unsigned int>(time(0)));
    
    int* random = new int[howMany];

    for (int i=0; i<howMany; i++) {
        int randNum = rand() % (totalNum-i);
        random[i] = numbers[randNum];
        
        int temp = numbers[randNum];
        numbers[randNum] = numbers[totalNum-1-i];
        numbers[totalNum-1] = temp;
    }
    
    return random;
}

vector<int> Game::parseIntegersFromCString(const char* str) {
    vector<int> integers;
    string numString = "";
    
    while(str[0] != '\0') {
        if (str[0] == ' ') {
            integers.push_back(atoi(numString.c_str()));
            numString = "";
        } else {
            numString += str[0];
        }
        str += 1;
    }
    integers.push_back(atoi(numString.c_str()));
    
    return integers;
}

std::string Game::getRoomDescription() {
    Nodes adj = m_rooms[getPlayerRoom()-1].getAdjacents();
    
    for (int i=0; i<3; i++)
        if (adj[i]->getNumber() == getWumpusRoom())
            return "You smell a stench.";
    
    for (int i=0; i<3; i++)
        if (adj[i]->getNumber() == getPitRooms()[0] || adj[i]->getNumber() == getPitRooms()[1])
            return "You feel a draft.";
    
    for (int i=0; i<3; i++)
        if (adj[i]->getNumber() == getBatRooms()[0] || adj[i]->getNumber() == getBatRooms()[1])
            return "You hear rustling of bat wings.";
    
    return "";
}

int Game::getEmptyRoom() {
    State st = getState();
    vector<int> emptyRooms;
    
    for (int i=1; i<21; i++)
        if (i!=st.playerRoom && i!=st.wumpusRoom && i!=st.batRooms[0] && i!=st.batRooms[1] && i!=st.pitRooms[0] && i!=st.pitRooms[1])
            emptyRooms.push_back(i);
    
    int randNum = rand() % 14;
    return emptyRooms[randNum];
}

void Game::setState(State state) {
    m_state = state;
}

State Game::getState() {
    return m_state;
}

void Game::setPlayerRoom(int r) {
    m_state.playerRoom = r;
}
int Game::getPlayerRoom() {
    return m_state.playerRoom;
}
void Game::setWumpusRoom(int r) {
    m_state.wumpusRoom = r;
}
int Game::getWumpusRoom() {
    return m_state.wumpusRoom;
}
void Game::setArrowRoom(int r) {
    m_state.arrowRoom = r;
}
int Game::getArrowRoom() {
    return m_state.arrowRoom;
}
void Game::setBatRooms(int r1, int r2) {
    m_state.batRooms[0] = r1;
    m_state.batRooms[1] = r2;
}
int* Game::getBatRooms() {
    return m_state.batRooms;
}
void Game::setPitRooms(int r1, int r2) {
    m_state.pitRooms[0] = r1;
    m_state.pitRooms[1] = r2;
}
int* Game::getPitRooms() {
    return m_state.pitRooms;
}

void Game::drawMaze() {
    cout << "     ______18______" << endl
    << "    /      |       \\ " << endl
    << "   /      _9__      \\ " << endl
    << "  /      /    \\      \\ " << endl
    << " /      /      \\      \\ " << endl
    << "17     8       10     19" << endl
    << "| \\   / \\      / \\   / | " << endl
    << "|  \\ /   \\    /   \\ /  | " << endl
    << "|   7     1--2     11  | " << endl
    << "|   |    /    \\    |   | " << endl
    << "|   6---5      3---12  | " << endl
    << "|   |    \\    /    |   | " << endl
    << "|    \\     4      /    | " << endl
    << "|     \\    |     /     | " << endl
    << " \\    15---14---13    / " << endl
    << "  \\   /          \\   / " << endl
    << "   \\ /            \\ / " << endl
    << "    16------------20"  << endl;
}

bool Game::playerMove(int inputNum) {
    Nodes adj = m_rooms[getPlayerRoom()-1].getAdjacents();
    
    if (inputNum == 0) {
        cout << "To move enter 'M' followed by a space and then a room number." << endl << endl;
        return false;
    }
    if (adj[0]->getNumber()!=inputNum && adj[1]->getNumber()!=inputNum && adj[2]->getNumber()!=inputNum) {
        cout << "You cannot move into this room" << endl << endl;
        return false;
    }
    setPlayerRoom(inputNum);
    
    bool movedByBats;
    do {
        movedByBats = false;
        
        // Pit
        if (getPlayerRoom() == getPitRooms()[0] || getPlayerRoom() == getPitRooms()[1]) {
            cout << "Aaaaaaaaahhhhhh.... \nYou fall into a pit and die." << endl;
            exitProgram();
        }
        
        // Bat
        if (getPlayerRoom() == getBatRooms()[0] || getPlayerRoom() == getBatRooms()[1]) {
            setBatRooms(getBatRooms()[0] == getPlayerRoom() ? getBatRooms()[1] : getBatRooms()[0], getEmptyRoom());
            setPlayerRoom((rand() % 20) + 1);
            movedByBats = true;
            
            cout << "Woah... you're flying! \nYou've just been transported by bats to room " << getPlayerRoom() << "." << endl;
        }
    }
    while (movedByBats);
    
    // Wumpus
    adj = m_rooms[getPlayerRoom()-1].getAdjacents();
    if (getPlayerRoom() == getWumpusRoom()) {
        if (getPlayerRoom() % 2 == 1) {
            cout << "You hear a slithering sound, as the Wumpus slips away.\nWhew, that was close!" << endl;
            setWumpusRoom(adj[0]->getNumber());
        } else {
            cout << "You briefly feel a slimy tentacled arm as your neck is snapped.\nIt is over." << endl;
            exitProgram();
        }
    }
    
    // Arrow
    if (getPlayerRoom() == getArrowRoom()) {
        cout << "Congratulations, you found the arrow and can once again shoot." << endl;
        setArrowRoom(-1);
    }
    
    // Save state to history
    m_sc.appendState(getState());
    
    cout << endl;
    return true;
}

bool Game::playerShoot(vector<int> rooms) {
    int arrowRoom = getPlayerRoom();
    bool ricochet = false;
    Nodes adj;
    
    for (int i=1; i<=rooms[0]; i++) {
        adj = m_rooms[arrowRoom-1].getAdjacents();
        if (rooms[i] == adj[0]->getNumber() || rooms[i] == adj[1]->getNumber() || rooms[i] == adj[2]->getNumber()) {
            arrowRoom = rooms[i];
        } else {
            cout << "Room " << rooms[i] << " is not adjacent. Arrow ricochets..." << endl;
            ricochet = true;
            arrowRoom = adj[0]->getNumber();
        }
        
        if (arrowRoom == getWumpusRoom()) {
            if (ricochet)
                cout << "Your arrow ricochet killed the Wumpus, you lucky dog!" << endl << "Accidental victory, but still you win!" << endl;
            else
                cout << "Wumpus has just been pierced by your deadly arrow!" << endl << "Congratulations on your victory, you awesome hunter." << endl;
            exitProgram();
        }
        
        if (arrowRoom == getPlayerRoom()) {
            if (ricochet)
                cout << "You just shot yourself, and are dying." << endl << "It didn't take long, you're dead." << endl;
            else
                cout << "You just shot yourself." << endl << "Maybe Darwin was right. You're dead." << endl;
            exitProgram();
        }
    }
    setArrowRoom(arrowRoom);
    
    // Save state to history
    m_sc.appendState(getState());
    
    cout << endl;
    return true;
}

void Game::displayCheat() {
    State state = getState();
    cout << "Cheating! Game elements are in the following rooms:" << endl
    << "Player\tWumpus\tBats1\tBats2\tPit1\tPit2\tArrow" << endl
    << "  " << state.playerRoom << "  \t  " << state.wumpusRoom << "  \t " << state.batRooms[0] << "  \t " << state.batRooms[1]
    << "  \t " << state.pitRooms[0] << "  \t " << state.pitRooms[1] << "  \t " << state.arrowRoom << endl << endl;
}

void Game::init(bool restart) {
    if (restart) {
        int input, input2;
        cout << "Enter the 7 room locations (1..20) for player, wumpus, bats1, bats2, pit1, pit2, and arrow: " << endl;
        
        cin >> input; setPlayerRoom(input);
        cin >> input; setWumpusRoom(input);
        cin >> input; cin >> input2; setBatRooms(input, input2);
        cin >> input; cin >> input2; setPitRooms(input, input2);
        cin >> input; setArrowRoom(input);
        cin.ignore();
        
        // Erasing all previous states
        m_sc.eraseAll();
    } else {
        int* randomNums = Game::getRandomNonRepeatingNumbers(0, 20, 6);
        setPlayerRoom(randomNums[0]+1);
        setWumpusRoom(randomNums[1]+1);
        setBatRooms(randomNums[2]+1, randomNums[3]+1);
        setPitRooms(randomNums[4]+1, randomNums[5]+1);
    }
    
    // Save state to history
    m_sc.appendState(getState());
    
    if (restart)
        cout << endl << "\tGame was restarted!" << endl << endl;
    
    loop();
}

void Game::loop() {
    int step = 0;
    string input;
    char inputCase;
    
    while (true) {
        cout << "\tYou are in room " << getPlayerRoom() << ". " << getRoomDescription() << endl
        << step+1 << ". Enter your move (or 'D' for directions): ";
        getline(cin, input);
        
        inputCase = tolower(input[0]);
        
        switch (inputCase) {
            case 'u':
                if (m_sc.revertState()) {
                    setState(m_sc.getState());
                    step -= 1;
                }
                else {
                    cout << "Sorry, you can't undo past the beginning of the game. Please retry." << endl;
                }
                cout << endl;
            break;
                
            case 'm':
            if ( playerMove( atoi(input.c_str()+1) ) )
                step += 1;
            break;
            
            case 's':
            if (getArrowRoom() == -1) {
                cout << "Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ";
                getline(cin, input);
                if ( playerShoot( parseIntegersFromCString(input.c_str()) ) )
                    step += 1;
            } else {
                cout << "Sorry, you can't shoot an arrow you don't have. Go find it." << endl << endl;
            }
            break;
            
            case 'r':
            init(true);
            break;
            
            case 'c':
            displayCheat();
            break;
            
            case 'd':
            drawMaze();
            cout << endl << "Hunt the Wumpus:" << endl
            << "The Wumpus lives in a completely dark cave of 20 rooms."
            << "Each room has 3 tunnels leading to other rooms." << endl << endl
            << "Hazards:" << endl
            << "1. Two rooms have bottomless pits in them. If you go there you fall and die." << endl
            << "2. Two other rooms have super-bats. If you go there, the bats grab you "
            << "and fly you to some random room, which could be troublesome. Then those "
            << "bats go to a new room different from where they came from and from the other bats." << endl
            << "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet "
            << "and is too heavy for bats to lift. Usually he is asleep. Two things wake him "
            << "up: Anytime you shoot an arrow, or you entering his room. The Wumpus will "
            << "move into the lowest-numbered adjacent room anytime you shoot an arrow. "
            << "When you move into the Wumpus' room, then he wakes and moves if he is in "
            << "an odd-numbered room, but stays still otherwise. After that, if he is in your "
            << "room, he snaps your neck and you die!" << endl << endl
            << "Moves:" << endl
            << "On each move you can do the following, where input can be upper or lower-case:" << endl
            << "1. Move into an adjacent room. To move enter 'M' followed by a space and then a room number." << endl
            << "2. Shoot your guided arrow through a list of up to three adjacent rooms, "
            << "which you specify. Your arrow ends up in the final room. To shoot enter 'S' "
            << "followed by the number of rooms (1..3), and then the list of the desired "
            << "number (up to 3) of adjacent room numbers, separated by spaces. If an "
            << "arrow can't go a direction because there is no connecting tunnel, it ricochets "
            << "and moves to the lowest-numbered adjacent room and continues doing this "
            << "until it has traveled the designated number of rooms. If the arrow hits the "
            << "Wumpus, you win! If the arrow hits you, you lose. You automatically pick up "
            << "the arrow if you go through a room with the arrow in it." << endl
            << "3. Enter 'R' to reset the person and hazard locations, useful for testing." << endl
            << "4. Enter 'C' to cheat and display current board positions." << endl
            << "5. Enter 'D' to display this set of instructions." << endl
            << "6. Enter 'P' to print the maze room layout." << endl
            << "7. Enter 'X' to exit the game." << endl << endl
            << "Good luck!" << endl << endl << endl;
            break;
            
            case 'p':
            drawMaze();
            cout << endl << endl;
            break;
            
            case 'x':
            exitProgram();
            break;
            
            default:
            break;
        }
    }
}

void Game::exitProgram() {
    cout << endl << "Exiting Program..." << endl;
    exit(0);
}
