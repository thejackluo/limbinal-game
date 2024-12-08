#ifndef METADATA_H
#define METADATA_H

#include <vector>
#include <string>

struct Character {
    std::string name;
    std::string role;
    std::string description;
};

// Forward declarations of classes referenced in globals
class Location;
class Item;
class People;
class EventManager;

// External global variables
extern std::vector<Character> characters;
extern std::vector<Location> locations;
extern std::vector<Item> items;
extern std::vector<People> people;

// External references to specifically mentioned People
extern People ryohashi;
extern People yumi;
extern People kakkeda;
extern People hiroto;
extern People suzumi;

extern EventManager eventManager;

// Declaration of the initialization function
void initializeMetadata();

#endif // METADATA_H