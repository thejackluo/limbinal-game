#include <vector>
#include <string>

#include "Location.cpp"
#include "Item.cpp"
#include "Event.cpp"
#include "People.cpp"

struct Character {
    std::string name;
    std::string role;
    std::string description;
};

std::vector<Character> characters = {
    {"Ryohashi", "Main Protagonist", "A socially reserved individual with a passion for technology and philosophy."},
    {"Yumi", "Deuteragonist", "A carefree girl fascinated by astrology and the stars."},
    {"Kakkeda", "Antagonist", "A perfectionist with a love for VR technology and psychological experiments."},
    {"Hiroto", "Friend", "A realistic and paranoid individual who supports Yumi's stance on Limbo."},
    {"Suzumi", "Friend", "A golden ponytail girl with a mysterious background."}
};

std::vector<Location> locations;
std::vector<Item> items;
std::vector<People> people;

// Initialize people
People ryohashi("Ryohashi", 100, 50, 30, 100);
People yumi("Yumi", 50, 0, 0, 0);
People kakkeda("Kakkeda", 50, 0, 0, 0);
People hiroto("Hiroto", 50, 0, 0, 0);
People suzumi("Suzumi", 50, 0, 0, 0);

EventContainer<Event> eventContainer;

void initializeMetadata() {
    // // Define dream world locations
    // Location segment1("Segment 1", "Part of the infinite street.");
    // Location segment2("Segment 2", "Part of the infinite street.");
    // Location segment3("Segment 3", "Part of the infinite street.");
    // Location segment4("Segment 4", "Part of the infinite street.");
    // Location segment5("Segment 5", "Part of the infinite street.");

    // // Connect dream world segments in a circular manner
    // segment1.addConnection("forward", &segment2);
    // segment2.addConnection("forward", &segment3);
    // segment3.addConnection("forward", &segment4);
    // segment4.addConnection("forward", &segment5);
    // segment5.addConnection("forward", &segment1);

    // std::vector<Location> dreamWorld = {segment1, segment2, segment3, segment4, segment5};

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

    std::vector<Location> physicalWorld = {mainHouse, suburbs, childhood, mainTown1, mainTown2, city1, city2, city3, city4};

    // Add locations to the global locations vector
    locations.insert(locations.end(), physicalWorld.begin(), physicalWorld.end());

    // Create and store events directly
    eventContainer.addEvent(Event(
        "Attack Event",
        Event::EventType::RANDOM,
        kakkeda.getName() + " is preparing to attack!",
        {"Attack"},
        { [=]() {
            int damage = rand() % 10 + 1;
            cout << kakkeda.getName() << " attacks " << ryohashi.getName() << " for " << damage << " damage!" << endl;
            ryohashi.modifyStats(-damage, 0, 0, 0);
        }},
        {}
    ));

    eventContainer.addEvent(Event(
        "Give Event",
        Event::EventType::RANDOM,
        yumi.getName() + " wants to give you something.",
        {"Accept"},
        { [=]() {
            int itemOrMoney = rand() % 2;
            if (itemOrMoney == 0) {
                int amount = rand() % 20 + 1;
                cout << yumi.getName() << " gives " << amount << " money to " << ryohashi.getName() << "!" << endl;
                ryohashi.modifyStats(0, 0, 0, amount);
            } else {
                Item gift(5, "Health Potion", ItemType::HEALTH, 20);
                cout << yumi.getName() << " gives a " << gift.getName() << " to " << ryohashi.getName() << "!" << endl;
                // ryohashi.addItem(gift);
            }
        }},
        {}
    ));

    eventContainer.addEvent(Event(
        "Message Event",
        Event::EventType::RANDOM,
        hiroto.getName() + " has a message for you.",
        {"Listen"},
        { [=]() {
            vector<string> messages = {
                "Stay strong, traveler!",
                "Beware of the cave ahead.",
                "You can do it!",
                "Remember to rest."
            };
            int randomIndex = rand() % messages.size();
            cout << hiroto.getName() << " says: \"" << messages[randomIndex] << "\"" << endl;
        }},
        {}
    ));

    mainHouse.addNPC(ryohashi);
    suburbs.addNPC(yumi);
    childhood.addNPC(kakkeda);
    mainTown1.addNPC(hiroto);
    mainTown2.addNPC(suzumi);

    std::vector<Item> itemContainer;
    itemContainer.push_back(Item(1, "Bandage", ItemType::HEALTH, 10));
    itemContainer.push_back(Item(2, "Memory Chip", ItemType::MEM, 25));
    itemContainer.push_back(Item(3, "Energy Drink", ItemType::ENERGY, 15));
    itemContainer.push_back(Item(4, "Cash", ItemType::MONEY, 10));
}
