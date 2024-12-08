using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <cstdlib>
#include <ctime>

#include "Item.h"
#include "InventoryContainer.h"
#include "Event.h"
#include "EventManager.h"
#include "Map.h"
#include "Location.h"
#include "Player.h"
#include "NPC.h"
#include "metadata.h"

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random events

    /*
        ========================
        Section 1: Initialize Game
        ========================
    */

    initializeMetadata(); // Initialize metadata

    // Create player
    Player player("Hero", 100, 50, 0, 0);
    player.setCurrentLocation(&locations[0]); // Assuming mainHouse is the first location

    /*
        ========================
        Section 2: Welcome Message
        ========================
    */
    cout << "Welcome to" << endl;
    cout << " ============================================= \n";
    cout << "  _      _           _     _             _ \n";
    cout << " | |    (_)         | |   (_)           | |\n";
    cout << " | |     _ _ __ ___ | |__  _ _ __   __ _| |\n";
    cout << " | |    | | '_ ` _ \\| '_ \\| | '_ \\ / _` | |\n";
    cout << " | |____| | | | | | | |_) | | | | | (_| | |\n";
    cout << " |______|_|_| |_| |_|_.__/|_|_| |_|\\__,_|_|\n";
    cout << "                                           \n";
    cout << " ============================================= \n";
    cout << "                                           \n";
    
    cout << "What is the name of your character: ";
    string name;
    try {
        cin >> name;
        if (cin.fail()) {
            throw runtime_error("Invalid input for name.");
        }
        player.setName(name);
        cout << "=============================================" << endl;
        cout << "Hello " << player.getName() << "! Welcome to Limbinal! You are about to embark on a journey across space to find your true purposes" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "HERE ARE THE INSTRUCTIONS BEFORE YOU EMBARK ON YOUR JOURNEY: " << endl;
    cout << "=============================================" << endl;
    cout << "Work in progress?" << endl;
    cout << "=============================================" << endl;

    cout << "Are you ready to begin your journey? (y/n): ";
    string ready;
    cin >> ready;

    if (ready == "y") {
        cout << "Let the adventure begin!" << endl;
    } else {
        cout << "No worries, feel free to come back later!" << endl;
        return 0;
    }

    /*
        ========================
        Section 3: Game Loop
        ========================
    */
    string command;
    Event* currentEvent = nullptr;
    // set current event to the first event in the event manager
    currentEvent = eventManager.getEvent(0);
    while (true) {
        /*
            ========================
            Section 3.1: UI Screen
            ========================
        */
        cout << "=============================================" << endl;
        cout << "LIMBINAL" << " - " << player.getCurrentLocation()->getName() << endl;
        cout << player.getCurrentLocation()->getDescription() << endl;
        cout << "---------------------------------------------" << endl;
        cout << "STORY: " << currentEvent->getMessage() << endl;
        
        cout << "=============================================" << endl;
       
        // Random event (TODO)
        Event* randomEvent = eventManager.getRandomEvent();
        if (randomEvent) {
            randomEvent->runEvent(player);
        }

    }

    return 0;
}

// ARCHIVE
//  cout << "Enter command: ";
//         cin >> command;

//         if (command == "quit") {
//             cout << "Exiting game. Goodbye!" << endl;
//             break;
//         } else if (command == "status") {
//             player.displayStats();
//         } else if (command == "map") {
//             gameMap.displayMap();
//         } else if (command == "inventory") {
//             player.displayInventory();
//         } else if (command == "people") {
//             // Display people's names for now
//             for (const auto& person : people) {
//                 cout << person.getName() << endl;
//             }
//         } else if (command == "move") {
//             cout << "Enter location name to move: ";
//             string locationName;
//             cin >> locationName;
//             Location* newLocation = gameMap.findLocation(locationName);
//             if (newLocation) {
//                 // If player location tracking is implemented:
//                 // map.movePlayer(player, newLocation);
//                 cout << "Moved to " << locationName << "." << endl;
//             } else {
//                 cout << "Invalid location." << endl;
//             }
//         } else {
//             cout << "Invalid command." << endl;
//         }

        // Future conditions for game end:
        // if (player.getHealth() <= 0) {
        //     cout << "You have lost all your health. Game over!" << endl;
        //     break;
        // }
        // if (player.getMemory() >= 100) {
        //     cout << "You have fully restored your memory. You win!" << endl;
        //     break;
        // }
        // if (player.getCurrentLocation() == city1) {
        //     cout << "You have reached City 1. Congratulations, you have found a new beginning!" << endl;
        //     break;
        // }