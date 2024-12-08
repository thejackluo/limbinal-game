#include "Map.h"
#include "Location.h"
#include "Player.h" // Needed because we call player.setCurrentLocation()

#include <iostream>
#include <algorithm>

Location* Map::addLocation(const std::string& name, const std::string& description) {
    Location* newLocation = new Location(name, description);
    locations.push_back(newLocation);
    return newLocation;
}

Location* Map::findLocation(const std::string& name) {
    for (Location* loc : locations) {
        if (loc->name == name) {
            return loc;
        }
    }
    return nullptr;
}

void Map::displayMap() const {
    std::cout << "Map Overview:" << std::endl;
    for (Location* loc : locations) {
        loc->display();
        std::cout << "--------------------" << std::endl;
    }
}

void Map::displayConnections(Location* location) const {
    if (location) {
        std::cout << "Connections from " << location->name << ": ";
        for (const auto& connection : location->connections) {
            std::cout << connection.first << " ";
        }
        std::cout << std::endl;
    }
}

// TODO: IF the player can move to the lcoation determined by the connections to the location, then move the player to the new location if not, then return false 
bool Map::movePlayer(Player& player, Location* newLocation) {
    // Check if the new location is a valid connection from the current location
    if (newLocation && player.getCurrentLocation()->connections.find(newLocation->name) != player.getCurrentLocation()->connections.end()) {
        player.setCurrentLocation(newLocation);
        return true;
    }
    return false;       
}

Map::~Map() {
    for (Location* loc : locations) {
        delete loc;
    }
}