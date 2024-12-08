#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>
#include <functional>
#include <utility>

#include "Player.h"
#include "Item.h"
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
          std::vector<std::pair<std::string, std::function<void()>>> resolutions,
          std::vector<SpecialEffect> effects);

    // getters
    std::string getName() const;
    EventType getType() const;
    std::string getMessage() const;
    std::vector<std::string> getChoices() const;
    std::vector<std::pair<std::string, std::function<void()>>> getResolutions() const;
    std::vector<SpecialEffect> getEffects() const;

    // setters
    void setName(const std::string& eventName);
    void setType(EventType eventType);
    void setMessage(const std::string& eventMessage);
    void setChoices(const std::vector<std::string>& eventChoices);
    void setResolutions(const std::vector<std::pair<std::string, std::function<void()>>>& eventResolutions);
    void setEffects(const std::vector<SpecialEffect>& eventEffects);

    // run the event
    void runEvent(class Player& player) const;

private:
    // private attributes
    std::string name; // name of the event
    EventType type; // type of the event
    std::string message; // initial message of the event
    std::vector<std::string> choices; // choices of the event (displayed to the player in the list)
    std::vector<std::pair<std::string, std::function<void()>>> resolutions; // resolutions of the event (functions to be called and also messages to be displayed)
    std::vector<SpecialEffect> effects; // effects of the event (changes to the player's attributes and items)

    // private methods
    int getPlayerChoice(class Player& player) const;
    void applySpecialEffects(class Player& player, const SpecialEffect& effect) const;
};

#endif // EVENT_H