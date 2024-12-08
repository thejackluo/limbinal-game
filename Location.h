#ifndef LOCATION_H
#define LOCATION_H

#include <string>
#include <vector>
#include <map>

// Forward declare classes referenced by pointer only if needed
class Item;
class People;
class Event;
class Location {
public:
    Location(std::string locName, std::string locDesc);

    // Getters
    std::string getName() const;
    std::string getDescription() const;
    // Setters
    void setName(const std::string& locName);
    void setDescription(const std::string& locDesc);
    
    // Graph collection and attributes
    void addConnection(const std::string& direction, Location* destination);
    void addItem(const Item& item);
    void addNPC(const People& npc);
    void addEvent(const Event& event);
    void removeItem(const Item& item);
    void removeNPC(const People& npc);
    void removeEvent(const Event& event);

    // Display
    void display() const;

    std::string name;
    std::string description;
    std::vector<Item> items;
    std::vector<People> npcs;
    std::vector<Event> events;
    std::map<std::string, Location*> connections;
};

#endif // LOCATION_H
