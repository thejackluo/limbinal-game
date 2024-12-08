#include "EventManager.h"
#include <iostream>
#include <functional> // for hash
#include <cstdlib>    // for rand()

void EventManager::addEvent(const Event& event) {
    size_t eventHash = std::hash<std::string>{}(event.getName());
    eventMap[eventHash] = event;
}

void EventManager::removeEvent(const std::string& eventName) {
    size_t eventHash = std::hash<std::string>{}(eventName);
    eventMap.erase(eventHash);
}

void EventManager::displayEvents() const {
    for (const auto& pair : eventMap) {
        std::cout << "Event: " << pair.second.getName() << std::endl;
    }
}

Event* EventManager::getEvent(const std::string& eventName) {
    size_t eventHash = std::hash<std::string>{}(eventName);
    auto it = eventMap.find(eventHash);
    if (it != eventMap.end()) {
        return &(it->second);
    }
    return nullptr;
}

Event* EventManager::getRandomEvent() {
    if (eventMap.empty()) return nullptr;
    auto it = eventMap.begin();
    std::advance(it, rand() % eventMap.size());
    return &(it->second);
}