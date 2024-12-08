#include "Event.h"
#include "Player.h" // Must have Player definition
#include "Item.h"    // Must have Item definition
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <limits>
#include <cstdlib>  // for rand(), if needed

Event::Event(std::string name, EventType type, std::string message,
             std::vector<std::string> choices,
             std::vector<std::function<void()>> resolutions,
             std::vector<SpecialEffect> effects)
    : name(std::move(name)), type(type), message(std::move(message)),
      choices(std::move(choices)), resolutions(std::move(resolutions)), effects(std::move(effects))
{}

std::string Event::getName() const {
    return name;
}


std::string Event::getMessage() const {
    return message;
}

std::vector<std::string> Event::getChoices() const {
    return choices;
}

std::vector<std::function<void()>> Event::getResolutions() const {
    return resolutions;
}

std::vector<Event::SpecialEffect> Event::getEffects() const {
    return effects;
}

void Event::setName(const std::string& eventName) {
    name = eventName;
}

void Event::setMessage(const std::string& eventMessage) {
    message = eventMessage;
}

void Event::setChoices(const std::vector<std::string>& eventChoices) {
    choices = eventChoices;
}

void Event::setResolutions(const std::vector<std::function<void()>>& eventResolutions) {
    resolutions = eventResolutions;
}

void Event::setEffects(const std::vector<SpecialEffect>& eventEffects) {
    effects = eventEffects;
}


void Event::runEvent(Player& player) const {
    std::cout << "Event: " << name << " | Type: " 
              << (type == EventType::RANDOM ? "Random" : "Story") << std::endl;
    std::cout << "Message: " << message << std::endl;

    if (!choices.empty()) {
        std::cout << "Choices: " << std::endl;
        for (size_t i = 0; i < choices.size(); ++i) {
            std::cout << i + 1 << ". " << choices[i] << std::endl;
        }

        int playerChoice = getPlayerChoice();
        std::cout << "You chose: " << choices[playerChoice - 1] << std::endl;

        if (playerChoice > 0 && static_cast<size_t>(playerChoice) <= resolutions.size()) {
            resolutions[playerChoice - 1]();
            if (static_cast<size_t>(playerChoice) <= effects.size()) {
                applySpecialEffects(player, effects[playerChoice - 1]);
            }
        }
    }
}

int Event::getPlayerChoice() const {
    int choice;
    std::cout << "Enter your choice (1-" << choices.size() << "): ";
    while (!(std::cin >> choice) || choice < 1 || static_cast<size_t>(choice) > choices.size()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and " << choices.size() << ": ";
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