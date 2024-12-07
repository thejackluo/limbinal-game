using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <functional>

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
                applySpecialEffects(player, effects[playerChoice - 1]);
            }
        }
    }

private:
    string name;
    EventType type;
    string message;
    vector<string> choices;
    vector<function<void()>> resolutions;
    vector<SpecialEffect> effects; // Store special effects for each resolution

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