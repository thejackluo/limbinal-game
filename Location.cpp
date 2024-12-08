#include "Location.h"
#include "Item.h"
#include "People.h"

#include <iostream>
#include <algorithm> // for std::find

Location::Location(std::string locName, std::string locDesc)
    : name(std::move(locName)), description(std::move(locDesc)) {}

// Getters
std::string Location::getName() const { return name; }
std::string Location::getDescription() const { return description; }

// Setters
void Location::setName(const std::string& locName) { name = locName; }
void Location::setDescription(const std::string& locDesc) { description = locDesc; }

// Adders
void Location::addConnection(const std::string& direction, Location* destination) { connections[direction] = destination; }
void Location::addItem(const Item& item) { items.push_back(item); }
void Location::addNPC(const People& npc) { npcs.push_back(npc); }
void Location::addEvent(const Event& event) { events.push_back(event); }

// Removers
void Location::removeItem(const Item& item) {
    auto it = std::find(items.begin(), items.end(), item);
    if (it != items.end()) {
        items.erase(it);
    } else {
        std::cout << "Item not found in this location." << std::endl;
    }
}

void Location::removeNPC(const People& npc) {
    auto it = std::find(npcs.begin(), npcs.end(), npc);
    if (it != npcs.end()) {
        npcs.erase(it);
    } else {
        std::cout << "NPC not found in this location." << std::endl;
    }
}

void Location::removeEvent(const Event& event) {
    auto it = std::find(events.begin(), events.end(), event);
    if (it != events.end()) {
        events.erase(it);
    } else {
        std::cout << "Event not found in this location." << std::endl;
    }
}

// Display (DEBUGGING)
void Location::display() const {
    std::cout << "Location: " << name << std::endl;
    std::cout << description << std::endl;

    if (!items.empty()) {
        std::cout << "Items here: ";
        for (const auto& item : items) {
            std::cout << item.getName() << " ";
        }
        std::cout << std::endl;
    }

    if (!npcs.empty()) {
        std::cout << "People here: ";
        for (const auto& npc : npcs) {
            std::cout << npc.getName() << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Connections: ";
    for (const auto& connection : connections) {
        std::cout << connection.first << " ";
    }
    std::cout << std::endl;
}