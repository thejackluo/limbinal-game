#include <vector>
#include "Location.cpp"
#include "Item.cpp"
#include "Event.cpp"

// Function to create an attack event
Event createAttackEvent(NPC& npc, Player& player) {
    return Event(
        "Attack Event",
        Event::EventType::RANDOM,
        npc.getName() + " is preparing to attack!",
        {"Attack"},
        { [&npc, &player]() {
            int damage = rand() % 10 + 1;
            cout << npc.getName() << " attacks " << player.getName() << " for " << damage << " damage!" << endl;
            player.modifyStats(-damage, 0, 0, 0);
        }},
        {}
    );
}

// Function to create a give event
Event createGiveEvent(NPC& npc, Player& player) {
    return Event(
        "Give Event",
        Event::EventType::RANDOM,
        npc.getName() + " wants to give you something.",
        {"Accept"},
        { [&npc, &player]() {
            int itemOrMoney = rand() % 2;
            if (itemOrMoney == 0) {
                int amount = rand() % 20 + 1;
                cout << npc.getName() << " gives " << amount << " money to " << player.getName() << "!" << endl;
                player.modifyStats(0, 0, 0, amount);
            } else {
                Item gift("Health Potion", 20, 0);
                cout << npc.getName() << " gives a " << gift.getName() << " to " << player.getName() << "!" << endl;
                player.addItem(gift);
            }
        }},
        {}
    );
}

// Function to create a send message event
Event createSendMessageEvent(NPC& npc) {
    return Event(
        "Message Event",
        Event::EventType::RANDOM,
        npc.getName() + " has a message for you.",
        {"Listen"},
        { [&npc]() {
            vector<string> messages = {
                "Stay strong, traveler!",
                "Beware of the cave ahead.",
                "You can do it!",
                "Remember to rest."
            };
            int randomIndex = rand() % messages.size();
            cout << npc.getName() << " says: \"" << messages[randomIndex] << "\"" << endl;
        }},
        {}
    );
}

std::vector<Location> locations;
std::vector<Item> items;

void initializeMetadata() {
    // Add locations
    Location forest("Forest", "A dense, dark forest");
    Location castle("Castle", "An ancient, abandoned castle");
    Location cave("Cave", "A damp, eerie cave");
    Location treasureRoom("Treasure Room", "A room filled with treasure");

    // Create Map?
    forest.addConnection("north", &castle);
    forest.addConnection("west", &cave);
    cave.addConnection("north", &treasureRoom);

    locations.push_back(forest);
    locations.push_back(castle);
    locations.push_back(cave);
    locations.push_back(treasureRoom);

    // Add items
    items.push_back(Item(1, "Health Potion", ItemType::HEALTH, 50));
    items.push_back(Item(2, "Energy Drink", ItemType::ENERGY, 30));

    // Example of adding events to an NPC
    NPC merchant("Merchant");
    Player player("Hero", 100, 50, 30, 100); // Example player

    merchant.addEvent(createAttackEvent(merchant, player));
    merchant.addEvent(createGiveEvent(merchant, player));
    merchant.addEvent(createSendMessageEvent(merchant));
}