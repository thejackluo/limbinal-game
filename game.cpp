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

    // Initialize metadata
    initializeMetadata();

    // Create a map
    Map map;

    // Create locations
    Location* mainHouse = map.addLocation("Main House", "The central location in the physical world.");
    Location* suburbs = map.addLocation("Suburbs", "Located south of the main house.");
    Location* childhood = map.addLocation("Childhood", "Located right of the main house.");
    Location* mainTown1 = map.addLocation("Main Town 1", "Located north of the main house.");
    Location* mainTown2 = map.addLocation("Main Town 2", "Located east of Main Town 1.");
    Location* city1 = map.addLocation("City 1", "Part of the city square.");
    Location* city2 = map.addLocation("City 2", "Part of the city square.");
    Location* city3 = map.addLocation("City 3", "Part of the city square.");
    Location* city4 = map.addLocation("City 4", "Part of the city square.");

    // Connect locations
    mainHouse->addConnection("south", suburbs);
    mainHouse->addConnection("right", childhood);
    mainHouse->addConnection("north", mainTown1);
    mainTown1->addConnection("east", mainTown2);
    mainTown1->addConnection("north", city3);
    city3->addConnection("west", city1);
    city3->addConnection("east", city2);
    city3->addConnection("north", city4);

    // Create player
    Player player("Hero", 100, 50, 0, 0);
    player.setCurrentLocation(mainHouse);

   
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
    EventManager eventManager;
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

        
        cout << "Enter command: ";
        cin >> command;

        if (command == "quit") {
            cout << "Exiting game. Goodbye!" << endl;
            break;
        } else if (command == "status") {
            player.displayStats();
        } else if (command == "map") {
            map.displayMap();
        } else if (command == "inventory") {
            player.displayInventory();
        } else if (command == "people") {
            // Display people's names for now
            for (const auto& person : people) {
                cout << person.getName() << endl;
            }
        } else if (command == "move") {
            cout << "Enter location name to move: ";
            string locationName;
            cin >> locationName;
            Location* newLocation = map.findLocation(locationName);
            if (newLocation) {
                // If player location tracking is implemented:
                // map.movePlayer(player, newLocation);
                cout << "Moved to " << locationName << "." << endl;
            } else {
                cout << "Invalid location." << endl;
            }
        } else {
            cout << "Invalid command." << endl;
        }

        // Random event
        Event* randomEvent = eventManager.getRandomEvent();
        if (randomEvent) {
            randomEvent->runEvent(player);
        }

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
    }

    return 0;
}