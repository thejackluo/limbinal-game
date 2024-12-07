using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Event {
public:
    enum class EventType {
        RANDOM,
        STORY
    };

    Event(string name, EventType type, string message, vector<string> choices, vector<function<void()>> resolutions)
        : name(name), type(type), message(message), choices(choices), resolutions(resolutions) {}

    void runEvent() const {
        cout << "Event: " << name << endl;
        cout << "Type: " << (type == EventType::RANDOM ? "Random" : "Story") << endl;
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
            }
        } else {
            cout << "No choices available. The event resolves automatically." << endl;
        }
    }

private:
    string name;
    EventType type;
    string message;
    vector<string> choices;
    vector<function<void()>> resolutions;

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
};