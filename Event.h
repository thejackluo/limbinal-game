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
    std::string getMessage() const;
    std::vector<std::string> getChoices() const;
    std::vector<std::function<void()>> getResolutions() const;
    std::vector<SpecialEffect> getEffects() const;

    void setName(const std::string& eventName);
    void setMessage(const std::string& eventMessage);
    void setChoices(const std::vector<std::string>& eventChoices);
    void setResolutions(const std::vector<std::function<void()>>& eventResolutions);
    void setEffects(const std::vector<SpecialEffect>& eventEffects);

    // We need Player fully defined here since we call its methods; 
    // We'll include "Player.h" in Event.cpp.
    void runEvent(class Player& player) const;

private:
    std::string name; // name of the event
    EventType type; // type of the event
    std::string message; // initial message of the event
    std::vector<std::string> choices; // choices of the event (displayed to the player in the list)
    std::vector<std::function<void()>> resolutions; // resolutions of the event (functions to be called and also messages to be displayed)
    std::vector<SpecialEffect> effects; // effects of the event (changes to the player's attributes and items)

    int getPlayerChoice() const;
    void applySpecialEffects(class Player& player, const SpecialEffect& effect) const;
};

#endif // EVENT_H