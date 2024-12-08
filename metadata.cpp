#include "metadata.h"
#include "Item.h"
#include "InventoryContainer.h"
#include "Event.h"
#include "EventManager.h"
#include "Map.h"
#include "Location.h"
#include "Player.h"
#include "NPC.h"

#include <iostream>
#include <cstdlib> // for rand()

// Define the global variables declared in metadata.h
/*
    =================================================================================
    Section 1: People (Player and NPCs)
    =================================================================================

*/
// std::vector<Character> characters = {
//     {"Ryohashi", "Main Protagonist", "A socially reserved individual with a passion for technology and philosophy."},
//     {"Yumi", "Deuteragonist", "A carefree girl fascinated by astrology and the stars."},
//     {"Kakkeda", "Antagonist", "A perfectionist with a love for VR technology and psychological experiments."},
//     {"Hiroto", "Friend", "A realistic and paranoid individual who supports Yumi's stance on Limbo."},
//     {"Suzumi", "Friend", "A golden ponytail girl with a mysterious background."}
// }; ORIGINAL, Ryohashi is player and the others are NPCs

std::vector<People> characters = {
    People("Ryohashi", 100, 50, 30, 100),
    People("Yumi", 50, 0, 0, 0),
    People("Kakkeda", 50, 0, 0, 0),
    People("Hiroto", 50, 0, 0, 0),
    People("Suzumi", 50, 0, 0, 0)
};

std::vector<Location> locations;
std::vector<Item> items;

EventManager eventManager;

void initializeMetadata() {
    /*
        =================================================================================
        Section 2: Map Locations
        =================================================================================
    */
    // Define physical world locations
    Location mainHouse("Main House", "The central location in the physical world.");
    Location suburbs("Suburbs", "Located south of the main house.");
    Location childhood("Childhood", "Located right of the main house.");
    Location mainTown1("Main Town 1", "Located north of the main house.");
    Location mainTown2("Main Town 2", "Located east of Main Town 1.");
    Location city1("City 1", "Part of the city square.");
    Location city2("City 2", "Part of the city square.");
    Location city3("City 3", "Part of the city square.");
    Location city4("City 4", "Part of the city square.");

    // Connect physical world locations
    mainHouse.addConnection("south", &suburbs);
    mainHouse.addConnection("right", &childhood);
    mainHouse.addConnection("north", &mainTown1);
    mainTown1.addConnection("east", &mainTown2);
    mainTown1.addConnection("north", &city3);
    city3.addConnection("west", &city1);
    city3.addConnection("east", &city2);
    city3.addConnection("north", &city4);

    std::vector<Location> physicalWorld = {
        mainHouse, suburbs, childhood, mainTown1, mainTown2, city1, city2, city3, city4
    };

    // Add locations to the global locations vector
    locations.insert(locations.end(), physicalWorld.begin(), physicalWorld.end());

    // Add NPCs to locations (People are treated as NPCs here)
    // Since 'Location' stores People by value, we must ensure People is compatible
    // If you need them as NPC or special classes, consider using NPC class or modify the approach.
    locations[0].addNPC(ryohashi); // mainHouse
    locations[1].addNPC(yumi);     // suburbs
    locations[2].addNPC(kakkeda);  // childhood
    locations[3].addNPC(hiroto);   // mainTown1
    locations[4].addNPC(suzumi);   // mainTown2


    /*
        =================================================================================
        Section 3: Events
        =================================================================================
    */
    // Create and store events directly
    eventManager.addEvent(Event(
        "Attack Event",
        Event::EventType::RANDOM,
        kakkeda.getName() + " is preparing to attack!",
        {"Attack"},
        { [=]() {
            int damage = rand() % 10 + 1;
            std::cout << kakkeda.getName() << " attacks " << ryohashi.getName() << " for " << damage << " damage!" << std::endl;
            ryohashi.modifyStats(-damage, 0, 0, 0);
        }},
        -1 // Random event, no specific number
    ));

    eventManager.addEvent(Event(
        "Give Event",
        Event::EventType::RANDOM,
        yumi.getName() + " wants to give you something.",
        {"Accept"},
        {[=]() {
            int itemOrMoney = rand() % 2;
            if (itemOrMoney == 0) {
                int amount = rand() % 20 + 1;
                std::cout << yumi.getName() << " gives " << amount << " money to " << ryohashi.getName() << "!" << std::endl;
                ryohashi.modifyStats(0, 0, 0, amount);
            } else {
                Item gift(5, "Health Potion", ItemType::HEALTH, 20);
                std::cout << yumi.getName() << " gives a " << gift.getName() << " to " << ryohashi.getName() << "!" << std::endl;
                // If needed, you'd have a Player class or inventory method for ryohashi.
                // ryohashi.addItem(gift); // If ryohashi was a Player instead of People.
            }
        }},
        -1 // Random event, no specific number
    ));

    eventManager.addEvent(Event(
        "Message Event",
        Event::EventType::RANDOM,
        hiroto.getName() + " has a message for you.",
        {"Listen"},
        { [=]() {
            std::vector<std::string> messages = {
                "Stay strong, traveler!",
                "Beware of the cave ahead.",
                "You can do it!",
                "Remember to rest."
            };
            int randomIndex = rand() % messages.size();
            std::cout << hiroto.getName() << " says: \"" << messages[randomIndex] << "\"" << std::endl;
        }},
        -1 // Random event, no specific number
    ));

    // New story event about Ryohashi in 2037 Tokyo
    eventManager.addEvent(Event(
        "2037 Tokyo Arrival",
        Event::EventType::STORY,
        "Ryohashi arrives in the bustling city of 2037 Tokyo, filled with neon lights and advanced technology.",
        {"Explore", "Rest"},
        { [=]() {
            std::cout << "Ryohashi decides to explore the city, taking in the sights and sounds of this futuristic metropolis." << std::endl;
        }, [=]() {
            std::cout << "Ryohashi finds a quiet place to rest and gather his thoughts." << std::endl;
        }},
        1 // Story event number
    ));

    /*
        =================================================================================
        Section 4: Items
        =================================================================================
    */
    // Initialize some items
    items.push_back(Item(1, "Bandage", ItemType::HEALTH, 10));
    items.push_back(Item(2, "Memory Chip", ItemType::MEM, 25));
    items.push_back(Item(3, "Energy Drink", ItemType::ENERGY, 15));
    items.push_back(Item(4, "Cash", ItemType::MONEY, 10));
}