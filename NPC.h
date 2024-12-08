#ifndef NPC_H
#define NPC_H

#include <vector>

#include "People.h"
#include "Event.h" // Include Event.h since we store Event objects directly.
#include "Location.h"


class Event; // Forward declaration (we store Events by value, so actually we need full definition)
class Player; // Forward declaration since we only reference Player by reference
class NPC : public People {
public:
    NPC(std::string name);

    void addEvent(const Event& event); // Add an event
    void triggerRandomEvent(Player& player); // FUTURE
    void displayStats() const override; // DEBUGGING
    void setCurrentLocation(Location* location);
    Location* getCurrentLocation() const;

private:
    std::vector<Event> events;
    Location* currentLocation;
};

#endif // NPC_H