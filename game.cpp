using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <cstdlib>
#include <ctime>

#include "Location.cpp"
#include "Event.cpp"
#include "People.cpp"
#include "Item.cpp"
#include "metadata.cpp"

int main(){
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
    // player.setCurrentLocation(mainHouse);

    /*
        ========================
        Section 2: Game Loop
        ========================
    */
    cout << "Welcome to Limbinal!" << endl;
    cout << "What is your name?" << endl;
    string name;
    try {
        cin >> name;
        if (cin.fail()) {
            throw runtime_error("Invalid input for name.");
        }
        player.setName(name);
        cout << "Hello " << player.getName() << "!" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    cout << "Instructions: " << endl;
    cout << "You are in a house. You can rest here." << endl;
    cout << "You can move to different locations by typing 'move'." << endl;
    cout << "You can check your status by typing 'status'." << endl;
    cout << "You can check the map by typing 'map'." << endl;
    cout << "You can display your inventory by typing 'inventory'." << endl;
    cout << "You can display people by typing 'people'." << endl;
    cout << "You can quit the game by typing 'quit'." << endl;

    // Game loop
    string command;
    while (true) {
        // Location event
        // cout << "You are at " << player.getCurrentLocation()->name << "." << endl;
        // player.getCurrentLocation()->display();

        // Player command
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
            for (const auto& person : people) {
                // cout << person.getName() << ": " << person.getDescription() << endl;
            }
        } else if (command == "move") {
            cout << "Available locations: " << endl;
            // map.displayConnections(player.getCurrentLocation());
            cout << "Enter location name to move: ";
            string locationName;
            cin >> locationName;
            Location* newLocation = map.findLocation(locationName);
            if (newLocation && map.movePlayer(player, newLocation)) {
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

        // Check game end conditions
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