#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <functional>

// Forward declare classes if needed
// If Player or Item classes are needed only as references/pointers, you could forward declare them here:
// class Player;
// class Item;

// If you need to use them directly, you must include their headers here.
// We'll include Player and Item in the .cpp since we need their full definitions there.
#include "Item.h"

class Item;   // forward declaration since we store them by value in SpecialEffect

class Event {
public:
    enum class EventType {
        RANDOM,
        STORY
    };

    struct SpecialEffect {
        std::vector<int> attributeChanges; // Changes to player's attributes
        std::vector<Item> items;           // Items to be added to the player
    };

    Event() = default;
    Event(std::string name, EventType type, std::string message,
          std::vector<std::string> choices,
          std::vector<std::function<void()>> resolutions,
          std::vector<SpecialEffect> effects);

    std::string getName() const;

    // We need Player fully defined here since we call its methods; 
    // We'll include "Player.h" in Event.cpp.
    void runEvent(class Player& player) const;

private:
    std::string name;
    EventType type;
    std::string message;
    std::vector<std::string> choices;
    std::vector<std::function<void()>> resolutions;
    std::vector<SpecialEffect> effects;

    int getPlayerChoice() const;
    void applySpecialEffects(class Player& player, const SpecialEffect& effect) const;
};

#endif // EVENT_H