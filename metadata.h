#ifndef METADATA_H
#define METADATA_H

#include <vector>
#include <string>
#include <map>

#include "Item.h"
#include "Event.h"
#include "EventManager.h"
#include "Location.h"
#include "People.h"
#include "Player.h"
#include "NPC.h"
#include "InventoryContainer.h"

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
class Player;
class NPC;

// External global variables
extern std::vector<Character> characters;
extern std::map<std::string, Location> locations;
extern InventoryContainer<Item> globalInventory;

// External references to specifically mentioned People
extern Player ryohashi;
extern NPC yumi;
extern NPC kakkeda;
extern NPC hiroto;
extern NPC suzumi;

extern EventManager eventManager;

// Declaration of the initialization function
void initializeMetadata();

#endif // METADATA_H