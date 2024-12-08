#include "metadata.h"
#include "Item.h"
#include "Event.h"
#include "EventManager.h"
#include "Location.h"
#include "People.h"
#include "Player.h"
#include "NPC.h"
#include "InventoryContainer.h"

#include <vector>
#include <map>
#include <iostream>
#include <cstdlib> // for rand()

std::vector<Character> characters;
std::map<std::string, Location> locations; // Use map for locations
InventoryContainer<Item> globalInventory;  // Use InventoryContainer for items
EventManager eventManager;

// Initialize Player and NPCs
Player ryohashi("Ryohashi", 100, 50, 30, 100);
NPC yumi("Yumi");
NPC kakkeda("Kakkeda");
NPC hiroto("Hiroto");
NPC suzumi("Suzumi");

void initializeMetadata() {
    /*
        =================================================================================
        Section 1: People (Player and NPCs)
        =================================================================================
    */
    //     {"Ryohashi", "Main Protagonist", "A socially reserved individual with a passion for technology and philosophy."},
    //     {"Yumi", "Deuteragonist", "A carefree girl fascinated by astrology and the stars."},
    //     {"Kakkeda", "Antagonist", "A perfectionist with a love for VR technology and psychological experiments."},
    //     {"Hiroto", "Friend", "A realistic and paranoid individual who supports Yumi's stance on Limbo."},
    //     {"Suzumi", "Friend", "A golden ponytail girl with a mysterious background."}

    /*
        =================================================================================
        Section 2: Map Locations
        =================================================================================
    */
    // Define physical world locations
    locations["Main House"] = Location("Main House", "The central location in the physical world.");
    locations["Suburbs"] = Location("Suburbs", "Located south of the main house.");
    locations["Childhood"] = Location("Childhood", "Located right of the main house.");
    locations["Main Town 1"] = Location("Main Town 1", "Located north of the main house.");
    locations["Main Town 2"] = Location("Main Town 2", "Located east of Main Town 1.");
    locations["City 1"] = Location("City 1", "Part of the city square.");
    locations["City 2"] = Location("City 2", "Part of the city square.");
    locations["City 3"] = Location("City 3", "Part of the city square.");
    locations["City 4"] = Location("City 4", "Part of the city square.");

    // Connect physical world locations
    locations["Main House"].addConnection("south", &locations["Suburbs"]);
    locations["Main House"].addConnection("right", &locations["Childhood"]);
    locations["Main House"].addConnection("north", &locations["Main Town 1"]);
    locations["Main Town 1"].addConnection("east", &locations["Main Town 2"]);
    locations["Main Town 1"].addConnection("north", &locations["City 3"]);
    locations["City 3"].addConnection("west", &locations["City 1"]);
    locations["City 3"].addConnection("east", &locations["City 2"]);
    locations["City 3"].addConnection("north", &locations["City 4"]);

    // Add NPCs to locations
    // locations["Main House"].addNPC(ryohashi); // RYOHASHI IS NOT A NPC
    locations["Suburbs"].addNPC(yumi);
    locations["Childhood"].addNPC(kakkeda);
    locations["Main Town 1"].addNPC(hiroto);
    locations["Main Town 2"].addNPC(suzumi);

    /*
        =================================================================================
        Section 3: Items
        =================================================================================
    */
    // Initialize some items
    globalInventory.addItem(Item(1, "Bandage", ItemType::HEALTH, 10));
    globalInventory.addItem(Item(2, "Memory Chip", ItemType::MEM, 25));
    globalInventory.addItem(Item(3, "Energy Drink", ItemType::ENERGY, 15));
    globalInventory.addItem(Item(4, "Cash", ItemType::MONEY, 10));

    /*
        =================================================================================
        Section 4: Events
        =================================================================================
    */
    // Create and store events directly
    eventManager.addEvent(Event(
        "Attack Event",
        Event::EventType::RANDOM,
        kakkeda.getName() + " is preparing to attack!",
        {"Attack"},
        { 
            {"Attack Resolution", [=]() {
                int damage = rand() % 10 + 1;
                std::cout << kakkeda.getName() << " attacks " << ryohashi.getName() << " for " << damage << " damage!" << std::endl;
                ryohashi.modifyStats(-damage, 0, 0, 0);
            }}
        },
        {}, // Add an empty vector for SpecialEffect
        -1  // Random event, no specific number
    ));

    eventManager.addEvent(Event(
        "Give Event",
        Event::EventType::RANDOM,
        yumi.getName() + " wants to give you something.",
        {"Accept"},
        { 
            {"Accept Resolution", [=]() {
                int itemOrMoney = rand() % 2;
                if (itemOrMoney == 0) {
                    int amount = rand() % 20 + 1;
                    std::cout << yumi.getName() << " gives " << amount << " money to " << ryohashi.getName() << "!" << std::endl;
                    ryohashi.modifyStats(0, 0, 0, amount);
                } else {
                    Item gift(5, "Health Potion", ItemType::HEALTH, 20);
                    std::cout << yumi.getName() << " gives a " << gift.getName() << " to " << ryohashi.getName() << "!" << std::endl;
                    // ryohashi.addItem(gift); // Uncomment if applicable
                }
            }}
        },
        {}, // Ensure this matches the expected type, e.g., std::vector<SpecialEffect>
        -1  // Ensure this matches the expected type, e.g., int
    ));

    eventManager.addEvent(Event(
        "Message Event",
        Event::EventType::RANDOM,
        hiroto.getName() + " has a message for you.",
        {"Listen"},
        { 
            {"Listen Resolution", [=]() {
                std::vector<std::string> messages = {
                    "Stay strong, traveler!",
                    "Beware of the cave ahead.",
                    "You can do it!",
                    "Remember to rest."
                };
                int randomIndex = rand() % messages.size();
                std::cout << hiroto.getName() << " says: \"" << messages[randomIndex] << "\"" << std::endl;
            }}
        },
        {}, // Ensure this matches the expected type, e.g., std::vector<SpecialEffect>
        -1  // Ensure this matches the expected type, e.g., int
    ));

    // New story event about Ryohashi in 2037 Tokyo
    eventManager.addEvent(Event(
        "2037 Tokyo Arrival",
        Event::EventType::STORY,
        "Ryohashi arrives in the bustling city of 2037 Tokyo, filled with neon lights and advanced technology.",
        {"Explore", "Rest"},
        { 
            {"Explore Resolution", [=]() {
                std::cout << "Ryohashi decides to explore the city, taking in the sights and sounds of this futuristic metropolis." << std::endl;
            }},
            {"Rest Resolution", [=]() {
                std::cout << "Ryohashi finds a quiet place to rest and gather his thoughts." << std::endl;
            }}
        },
        {}, // Add an empty vector for SpecialEffect
        1   // Story event number
    ));

}