#include "Event.h"
#include "Player.h" // Must have Player definition
#include "Item.h"    // Must have Item definition
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <cstdlib>  // for rand(), if needed
#include <functional>
#include <string>
#include <vector>

// constructor
Event::Event(std::string name, EventType type, std::string message,
             std::vector<std::string> choices,
             std::vector<std::pair<std::string, std::function<void()>>> resolutions,
             std::vector<SpecialEffect> effects)
    : name(std::move(name)), type(type), message(std::move(message)),
      choices(std::move(choices)), resolutions(std::move(resolutions)), effects(std::move(effects))
{}

// getters
std::string Event::getName() const { return name; }
Event::EventType Event::getType() const { return type; }
std::string Event::getMessage() const { return message; }
std::vector<std::string> Event::getChoices() const { return choices; }
std::vector<std::pair<std::string, std::function<void()>>> Event::getResolutions() const { return resolutions; }
std::vector<Event::SpecialEffect> Event::getEffects() const { return effects; }

// setters
void Event::setName(const std::string& eventName) { name = eventName; }
void Event::setType(EventType eventType) { type = eventType; }
void Event::setMessage(const std::string& eventMessage) { message = eventMessage; }
void Event::setChoices(const std::vector<std::string>& eventChoices) { choices = eventChoices; }
void Event::setResolutions(const std::vector<std::pair<std::string, std::function<void()>>>& eventResolutions) { resolutions = eventResolutions; }
void Event::setEffects(const std::vector<SpecialEffect>& eventEffects) { effects = eventEffects; }


void Event::runEvent(Player& player) const {
    // Display event type and story
    std::cout << "=============================================" << std::endl;
    std::cout << "EVENT TYPE: " << (type == EventType::RANDOM ? "EVENT" : "STORY") << std::endl;
    std::cout << message << std::endl; // Multi-line story support
    std::cout << "---------------------------------------------" << std::endl;

    // Display choices
    if (!choices.empty()) {
        std::cout << "CHOICES:" << std::endl;
        for (size_t i = 0; i < choices.size(); ++i) {
            std::cout << "[" << i + 1 << "]: " << choices[i] << std::endl;
        }
        std::cout << "=============================================" << std::endl;

        // Get player's choice
        int playerChoice = getPlayerChoice(player);

        // Display resolution message
        std::cout << "============================" << std::endl;
        const auto& resolution = resolutions[playerChoice - 1];
        std::cout << "RESOLUTION: " << resolution.first << std::endl;

        // Apply resolution function
        resolution.second();

        // Apply special effects (if any)
        if (static_cast<size_t>(playerChoice) <= effects.size()) {
            applySpecialEffects(player, effects[playerChoice - 1]);
        }

        // Display stat changes and items
        std::cout << "============================" << std::endl;
        player.displayStats();
        player.displayInventory();
    } else {
        std::cout << "No choices available for this event." << std::endl;
    }
}

int Event::getPlayerChoice(Player& player) const {
    int choice;
    std::cout << player.getName() << ", please embark on a choice (1-" << choices.size() << "): ";
    while (!(std::cin >> choice) || choice < 1 || static_cast<size_t>(choice) > choices.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Sorry, that is not a valid choice. Please enter a number between 1 and " << choices.size() << ": ";
    }
    return choice;
}

void Event::applySpecialEffects(Player& player, const SpecialEffect& effect) const {
    // Apply attribute changes
    if (effect.attributeChanges.size() >= 4) {
        player.modifyStats(effect.attributeChanges[0],
                           effect.attributeChanges[1],
                           effect.attributeChanges[2],
                           effect.attributeChanges[3]);
    }

    // Add items to the player
    for (const Item& item : effect.items) {
        player.addItem(item);
    }
}

std::vector<std::pair<std::string, std::function<void()>>> resolutions = {
    {"Resolution 1", []() { /* some action */ }},
    {"Resolution 2", []() { /* another action */ }}
};
