#include "NPC.h"
#include "Event.h"
#include "Player.h"
#include <iostream>
#include <cstdlib> // for rand()

NPC::NPC(std::string name)
    : People(std::move(name), 50, 0, 0, 0), currentLocation(nullptr) {}

void NPC::addEvent(const Event& event) {
    events.push_back(event);
}

void NPC::triggerRandomEvent(Player& player) {
    if (!events.empty()) {
        int randomIndex = rand() % events.size();
        events[randomIndex].runEvent(player);
    } else {
        std::cout << name << " has no events to trigger." << std::endl;
    }
}

void NPC::displayStats() const {
    // NPC only displays name and health as per original code
    std::cout << "Name: " << name << std::endl;
    std::cout << "Health: " << health << std::endl;
}

void NPC::setCurrentLocation(Location* location) {
    currentLocation = location;
}

Location* NPC::getCurrentLocation() const {
    return currentLocation;
}