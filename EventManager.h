#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <string>
#include <unordered_map>
#include "Event.h"  // Need Event definition

class EventManager {
public:
    void addEvent(const Event& event);
    void removeEvent(const std::string& eventName);
    void displayEvents() const;
    Event* getEvent(const std::string& eventName);
    Event* getRandomEvent();
    // Event* getEventByNumber(int eventNumber); // TODO: implement this

private:
    std::unordered_map<size_t, Event> eventMap;
};

#endif // EVENTMANAGER_H