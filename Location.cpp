#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Item.cpp"
using namespace std;

class Location {
public:
    string name;
    string description;
    vector<Item> items;
    map<string, Location*> connections;

    Location(string locName, string locDesc)
        : name(locName), description(locDesc) {}

    void addConnection(string direction, Location* destination) {
        connections[direction] = destination;
    }

    void display() {
        cout << "Location: " << name << endl;
        cout << description << endl;
        if (!items.empty()) {
            cout << "Items here: ";
            for (const auto& item : items) {
                cout << item << " ";
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
        for (Location* loc : locations) {
            loc->display();
            cout << "--------------------" << endl;
        }
    }

    ~Map() {
        for (Location* loc : locations) {
            delete loc;
        }
    }
};