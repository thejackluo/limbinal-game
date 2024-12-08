#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Location;  // forward declaration of Location
class Player;    // forward declaration of Player

class Map {
public:
    Location* addLocation(const std::string& name, const std::string& description);
    Location* findLocation(const std::string& name);
    bool movePlayer(Player& player, Location* newLocation);

    // Display (DEBUGGING)
    void displayMap() const;
    void displayConnections(Location* location) const;

    ~Map();

private:
    std::vector<Location*> locations;
};

#endif // MAP_H
