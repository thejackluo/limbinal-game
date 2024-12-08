#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include <map>

// Forward declare classes referenced by pointer only if needed
class Item;
class People;

class Location {
public:
    Location(std::string locName, std::string locDesc);

    // Getters
    std::string getName() const;
    std::string getDescription() const;

    // Setters
    void setName(const std::string& locName);
    void setDescription(const std::string& locDesc);
    
    void addConnection(const std::string& direction, Location* destination);
    void addItem(const Item& item);
    void addNPC(const People& npc);
    void removeItem(const Item& item);
    void removeNPC(const People& npc);
    void display() const;

    std::string name;
    std::string description;
    std::vector<Item> items;
    std::vector<People> npcs;
    std::map<std::string, Location*> connections;
};

#endif // LOCATION_H
