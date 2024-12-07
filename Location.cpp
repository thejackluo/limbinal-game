#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Item.cpp"
#include "People.cpp"
using namespace std;

class Location {
public:
    string name;
    string description;
    vector<Item> items;
    vector<People> npcs;
    map<string, Location*> connections;

    Location(string locName, string locDesc)
        : name(locName), description(locDesc) {}

    void addConnection(string direction, Location* destination) {
        connections[direction] = destination;
    }

    void addItem(const Item& item) {
        items.push_back(item);
    }

    void addNPC(const People& npc) {
        npcs.push_back(npc);
    }

    void removeItem(const Item& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        } else {
            cout << "Item not found in this location." << endl;
        }
    }

    void removeNPC(const People& npc) {
        auto it = std::find(npcs.begin(), npcs.end(), npc);
        if (it != npcs.end()) {
            npcs.erase(it);
        } else {
            cout << "NPC not found in this location." << endl;
        }
    }

    void display() {
        cout << "Location: " << name << endl;
        cout << description << endl;

        if (!items.empty()) {
            cout << "Items here: ";
            for (const auto& item : items) {
                cout << item.getName() << " ";
            }
            cout << endl;
        }

        if (!npcs.empty()) {
            cout << "People here: ";
            for (const auto& npc : npcs) {
                cout << npc.getName() << " ";
            }
            cout << endl;
        }

        cout << "Connections: ";
        for (const auto& connection : connections) {
            cout << connection.first << " ";
        }
        cout << endl;
    }
};

class Map {
public:
    vector<Location*> locations;

    Location* addLocation(string name, string description) {
        Location* newLocation = new Location(name, description);
        locations.push_back(newLocation);
        return newLocation;
    }

    Location* findLocation(string name) {
        for (Location* loc : locations) {
            if (loc->name == name) {
                return loc;
            }
        }
        return nullptr;
    }

    void displayMap() {
        cout << "Map Overview:" << endl;
        for (Location* loc : locations) {
            loc->display();
            cout << "--------------------" << endl;
        }
    }

    void displayConnections(Location* location) {
        cout << "Connections from " << location->name << ": ";
        for (const auto& connection : location->connections) {
            cout << connection.first << " ";
        }
        cout << endl;
    }

    bool movePlayer(Player& player, Location* newLocation) {
        if (newLocation) {
            player.setCurrentLocation(newLocation);
            return true;
        }
        return false;
    }

    ~Map() {
        for (Location* loc : locations) {
            delete loc;
        }
    }
};