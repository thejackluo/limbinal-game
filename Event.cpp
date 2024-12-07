using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <unordered_map>

#include "Item.cpp"

class Event {
public:
    enum class EventType {
        RANDOM,
        STORY
    };

    struct SpecialEffect {
        vector<int> attributeChanges; // Changes to player's attributes
        vector<Item> items;           // Items to be added to the player
    };

    Event(string name, EventType type, string message, vector<string> choices, vector<function<void()>> resolutions, vector<SpecialEffect> effects)
        : name(name), type(type), message(message), choices(choices), resolutions(resolutions), effects(effects) {}

    string getName() const { return name; }

    void runEvent(Player& player) const {
        cout << "Event: " << name << " | Type: " << (type == EventType::RANDOM ? "Random" : "Story") << endl;
        cout << "Message: " << message << endl;

        if (!choices.empty()) {
            cout << "Choices: " << endl;
            for (size_t i = 0; i < choices.size(); ++i) {
                cout << i + 1 << ". " << choices[i] << endl;
            }

            int playerChoice = getPlayerChoice();
            cout << "You chose: " << choices[playerChoice - 1] << endl;

            if (playerChoice > 0 && playerChoice <= resolutions.size()) {
                resolutions[playerChoice - 1]();
                if (playerChoice <= effects.size()) {
                    applySpecialEffects(player, effects[playerChoice - 1]);
                }
            }
        }
    }

private:
    string name;
    EventType type;
    string message;
    vector<string> choices;
    vector<function<void()>> resolutions;
    vector<SpecialEffect> effects;

    int getPlayerChoice() const {
        int choice;
        cout << "Enter your choice (1-" << choices.size() << "): ";
        while (!(cin >> choice) || choice < 1 || choice > choices.size()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a number between 1 and " << choices.size() << ": ";
        }
        return choice;
    }

    void applySpecialEffects(Player& player, const SpecialEffect& effect) const {
        // Apply attribute changes
        if (effect.attributeChanges.size() >= 4) {
            player.modifyStats(effect.attributeChanges[0], effect.attributeChanges[1], effect.attributeChanges[2], effect.attributeChanges[3]);
        }

        // Add items to the player
        for (const Item& item : effect.items) {
            player.addItem(item);
        }
    }
};

class EventManager {
public:
    void addEvent(const Event& event) {
        size_t eventHash = hash<string>{}(event.getName());
        eventMap[eventHash] = event;
    }

    void removeEvent(const string& eventName) {
        size_t eventHash = hash<string>{}(eventName);
        eventMap.erase(eventHash);
    }

    void displayEvents() const {
        for (const auto& pair : eventMap) {
            cout << "Event: " << pair.second.getName() << endl;
        }
    }

    Event* getEvent(const string& eventName) {
        size_t eventHash = hash<string>{}(eventName);
        auto it = eventMap.find(eventHash);
        if (it != eventMap.end()) {
            return &(it->second);
        }
        return nullptr;
    }

private:
    unordered_map<size_t, Event> eventMap;
};
