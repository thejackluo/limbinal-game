#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <map>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "Item.h"
#include "InventoryContainer.h"
#include "Event.h"
#include "EventManager.h"
#include "Map.h"
#include "Location.h"
#include "Player.h"
#include "NPC.h"
#include "metadata.h"

using namespace std;

// Optional: function to clear the console screen for a cleaner UI per turn
void clearScreen() {
#ifdef _WIN32
    system("CLS");
#else
    system("clear");
#endif
}

// A helper function to display a nice separator line
void printSeparator(char c = '=', int length = 45) {
    for (int i = 0; i < length; i++) cout << c;
    cout << "\n";
}

// Function to display the main header and location info
void displayLocationInfo(const Player &player) {
    printSeparator('=');
    cout << "LIMBINAL - " << player.getCurrentLocation()->getName() << "\n";
    cout << player.getCurrentLocation()->getDescription() << "\n";
    printSeparator('-');
}

// Display main action menu
void displayMainMenu() {
    cout << "What would you like to do?\n";
    cout << "[1] Move to another location\n";
    cout << "[2] Use an item\n";
    cout << "[3] Stay here\n";
    cout << "[4] Inspect the location\n";
    cout << "[5] Check status\n";
    cout << "[6] Quit\n";
    cout << "Enter a number: ";
}

// After story events or random events are run, we can show a short pause
void pauseForUser() {
    cout << "\n(Press Enter to continue...)\n";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random events

    initializeMetadata(); // Initialize metadata

    // Use Ryohashi as the player
    ryohashi.setCurrentLocation(&locations["Main House"]);

    // Welcome message
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
        ryohashi.setName(name);
        cout << "=============================================" << endl;
        cout << "Hello " << ryohashi.getName() << "! Welcome to Limbinal! You are about to embark on a journey across space to find your true purposes\n\n";
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "HERE ARE THE INSTRUCTIONS BEFORE YOU EMBARK ON YOUR JOURNEY:\n";
    cout << " - Your goal is to find your true purpose in life by exploring the world and interacting with people.\n";
    cout << " - You will be given a series of events to complete, each with a set of choices.\n";
    cout << " - Your choices will affect your attributes and the story will unfold differently based on your choices.\n";
    cout << " - You can also explore the world by moving to different locations.\n";
    cout << "Let the adventure begin!\n\n";

    cout << "Are you ready to begin your journey? (y/n): ";
    string ready;
    cin >> ready;

    if (ready == "y") {
        cout << "Let the adventure begin!\n";
    } else {
        cout << "No worries, feel free to come back later!\n";
        return 0;
    }

    // The main game loop
    while (true) {
        clearScreen();
        displayLocationInfo(ryohashi);

        Location* currentLoc = ryohashi.getCurrentLocation();

        // Check for STORY event
        Event* storyEvent = nullptr;
        for (auto& evt : currentLoc->events) {
            if (evt.getType() == Event::EventType::STORY) {
                storyEvent = &evt;
                break;
            }
        }

        if (storyEvent) {
            storyEvent->runEvent(ryohashi);
            currentLoc->removeEvent(*storyEvent);
            pauseForUser();
            continue;
        }

        // No story event, show main menu
        displayMainMenu();

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            pauseForUser();
            continue;
        }

        clearScreen();
        displayLocationInfo(ryohashi);

        switch (choice) {
            case 1: {
                cout << "Available connections:\n";
                for (const auto& conn : currentLoc->connections) {
                    cout << "- " << conn.first << " -> " << conn.second->getName() << "\n";
                }
                cout << "Enter direction: ";
                string direction;
                cin >> direction;
                if (currentLoc->connections.find(direction) != currentLoc->connections.end()) {
                    ryohashi.setCurrentLocation(currentLoc->connections[direction]);
                    cout << "You move to " << ryohashi.getCurrentLocation()->getName() << ".\n";
                } else {
                    cout << "Invalid direction.\n";
                }
                pauseForUser();
                break;
            }
            case 2: {
                cout << "Your inventory:\n";
                ryohashi.displayInventory();
                cout << "Enter item name to use (or 'cancel'): ";
                string itemName;
                cin >> itemName;
                if (itemName != "cancel") {
                    ryohashi.useItemByName(itemName);
                }
                pauseForUser();
                break;
            }
            case 3: {
                // Stay: random event if NPC present
                if (!currentLoc->npcs.empty()) {
                    Event* randomEvent = eventManager.getRandomEvent();
                    if (randomEvent) {
                        randomEvent->runEvent(ryohashi);
                    } else {
                        cout << "Nothing special happens.\n";
                    }
                } else {
                    cout << "You wait, but nothing occurs.\n";
                }
                pauseForUser();
                break;
            }
            case 4: {
                cout << "Items at this location:\n";
                if (currentLoc->items.empty()) {
                    cout << "No items here.\n";
                } else {
                    for (const auto& i : currentLoc->items) {
                        i.display();
                    }
                    cout << "Enter the ID of the item to pick it up, or 0 for none: ";
                    int itemId;
                    cin >> itemId;

                    if (itemId != 0) {
                        auto it = std::find_if(currentLoc->items.begin(), currentLoc->items.end(),
                                            [&](const Item& itm) { return itm.getId() == itemId; });
                        if (it != currentLoc->items.end()) {
                            ryohashi.addItem(*it);
                            currentLoc->items.erase(it);
                            cout << "You picked up item with ID " << itemId << ".\n";
                        } else {
                            cout << "No item with that ID here.\n";
                        }
                    }
                }
                pauseForUser();
                break;
            }
            case 5: {
                // Check status
                ryohashi.displayStats();
                // Show inventory once here
                cout << "\nYour Inventory:\n";
                ryohashi.displayInventory();
                pauseForUser();
                break;
            }
            case 6:
                cout << "Exiting game. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
                pauseForUser();
                break;
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