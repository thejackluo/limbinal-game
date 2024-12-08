using namespace std;
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

int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed for random events

    /*
        ========================
        Section 1: Initialize Game
        ========================
    */

    initializeMetadata(); // Initialize metadata

    // Use Ryohashi as the player
    ryohashi.setCurrentLocation(&locations["Main House"]);

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
        ryohashi.setName(name);
        cout << "=============================================" << endl;
        cout << "Hello " << ryohashi.getName() << "! Welcome to Limbinal! You are about to embark on a journey across space to find your true purposes" << endl << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    cout << "HERE ARE THE INSTRUCTIONS BEFORE YOU EMBARK ON YOUR JOURNEY: " << endl;
    cout << " - Your goal is to find your true purpose in life by exploring the world and interacting with people." << endl;
    cout << " - You will be given a series of events to complete, each with a set of choices." << endl;
    cout << " - Your choices will affect your attributes and the story will unfold differently based on your choices." << endl;
    cout << " - You can also explore the world by moving to different locations." << endl;
    cout << "Let the adventure begin!" << endl << endl;

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
    currentEvent = eventManager.getEvent("2037 Tokyo Arrival");
    while (true) {
        // 1. Display Location & Basic Info
        cout << "=============================================\n";
        cout << "LIMBINAL - " << ryohashi.getCurrentLocation()->getName() << "\n";
        cout << ryohashi.getCurrentLocation()->getDescription() << "\n";
        
        Location* currentLoc = ryohashi.getCurrentLocation();
        
        // 2. Check if there's a STORY event in the current location
        Event* storyEvent = nullptr;
        for (auto& evt : currentLoc->events) {
            if (evt.getType() == Event::EventType::STORY) {
                storyEvent = &evt;
                break;
            }
        }

        if (storyEvent) {
            // Run the story event
            storyEvent->runEvent(ryohashi);
            // Remove the event after completion
            currentLoc->removeEvent(*storyEvent);
            
            // After a story event, possibly continue the loop.
            // Maybe story events end the turn, or maybe the player can still act.
            // For simplicity, let's end this iteration.
            continue;
        }

        // 3. If no story event, present default choices.
        cout << "What would you like to do?\n";
        cout << "[1] Move to another location\n";
        cout << "[2] Use an item\n";
        cout << "[3] Stay here\n";
        cout << "[4] Inspect the location\n";
        cout << "[5] Check status\n";
        cout << "[6] Quit\n";
        cout << "Enter a number: ";
        
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                // Move
                cout << "Where would you like to go? Available connections:\n";
                for (const auto& conn : currentLoc->connections) {
                    cout << "- " << conn.first << " (" << conn.second->getName() << ")\n";
                }
                cout << "Enter direction or location name: ";
                std::string direction;
                cin >> direction;
                if (currentLoc->connections.find(direction) != currentLoc->connections.end()) {
                    ryohashi.setCurrentLocation(currentLoc->connections[direction]);
                    cout << "You move to " << ryohashi.getCurrentLocation()->getName() << ".\n";
                } else {
                    cout << "You can't go that way.\n";
                }
                break;
            }
            case 2: {
                // Use item
                cout << "Your inventory:\n";
                ryohashi.displayInventory();
                cout << "Enter item name to use (or 'cancel'): ";
                std::string itemName;
                cin >> itemName;
                if (itemName != "cancel") {
                    // You would need a method to find an item by name in player's inventory
                    // or prompt the user with indexed choices.
                    // For now, assume we have a method to get an item by name.
                    // Item item = player.getItemByName(itemName);
                    // if valid item, player.useItem(item);
                }
                break;
            }
            case 3: {
                // Stay
                // Potentially trigger a random event if NPC is present
                bool npcPresent = !currentLoc->npcs.empty();
                if (npcPresent) {
                    Event* randomEvent = eventManager.getRandomEvent();
                    if (randomEvent) {
                        randomEvent->runEvent(ryohashi);
                    } else {
                        cout << "Nothing noteworthy happens.\n";
                    }
                } else {
                    cout << "You linger a bit, but nothing special occurs.\n";
                }
                break;
            }
            case 4: {
                // Inspect location
                cout << "Items at this location:\n";
                if (currentLoc->items.empty()) {
                    cout << "No items here.\n";
                } else {
                    for (const auto& i : currentLoc->items) {
                        i.display();
                    }
                    cout << "Enter the name of the item to pick it up, or 'none': ";
                    std::string pickChoice;
                    cin >> pickChoice;
                    if (pickChoice != "none") {
                        // Find the item, add to player's inventory, remove from location
                        auto it = std::find_if(currentLoc->items.begin(), currentLoc->items.end(),
                                            [&](const Item& itm){ return itm.getName() == pickChoice; });
                        if (it != currentLoc->items.end()) {
                            ryohashi.addItem(*it);
                            currentLoc->items.erase(it);
                            cout << "You picked up " << pickChoice << ".\n";
                        } else {
                            cout << "No such item here.\n";
                        }
                    }
                }
                break;
            }
            case 5: {
                // Check status
                ryohashi.displayStats();
                break;
            }
            case 6: {
                cout << "Exiting game. Goodbye!\n";
                return 0;
            }
            default:
                cout << "Invalid choice.\n";
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