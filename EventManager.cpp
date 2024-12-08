#include "EventManager.h"
#include <iostream>
#include <functional> // for hash
#include <cstdlib>    // for rand()


void EventManager::addEvent(const Event& event) {
    size_t eventHash = std::hash<std::string>{}(event.getName());
    eventMap[eventHash] = event;
}

// TODO: ensure that if the event doesn't exist, the program doesn't crash (might not be that important)
void EventManager::removeEvent(const std::string& eventName) {
    size_t eventHash = std::hash<std::string>{}(eventName);
    eventMap.erase(eventHash);
}

// DEBUGGING: display all events
void EventManager::displayEvents() const {
    for (const auto& pair : eventMap) {
        std::cout << "Event: " << pair.second.getName() << std::endl;
    }
}

// get an event by name
Event* EventManager::getEvent(const std::string& eventName) {
    size_t eventHash = std::hash<std::string>{}(eventName);
    auto it = eventMap.find(eventHash);
    if (it != eventMap.end()) {
        return &(it->second);
    }
    return nullptr;
}

// get a random event (only return events with type == RANDOM)
Event* EventManager::getRandomEvent() {
    // get all events with type == RANDOM
    std::vector<Event> randomEvents;
    for (const auto& pair : eventMap) {
        if (pair.second.getType() == Event::EventType::RANDOM) {
            randomEvents.push_back(pair.second);
        }
    }
    // return a random event from the vector
    if (randomEvents.empty()) return nullptr;
    auto it = randomEvents.begin();
    std::advance(it, rand() % randomEvents.size());
    return &(*it);
}

