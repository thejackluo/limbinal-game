#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "Item.cpp"
#include "Event.cpp"
using namespace std;

class People {
public:
    string name;
    int health;
    int energy;
    int mem;
    int money;

    People(string name, int health, int energy, int mem, int money)
        : name(name), health(health), energy(energy), mem(mem), money(money) {}

    void setName(string name) {
        this->name = name;
    }

    string getName() const {
        return name;
    }

    void modifyStats(int healthChange, int energyChange, int memChange, int moneyChange) {
        health += healthChange;
        energy += energyChange;
        mem += memChange;
        money += moneyChange;
        if (health < 0) health = 0;
        if (energy < 0) energy = 0;
        if (money < 0) money = 0;
    }

    virtual void displayStats() const {
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
        cout << "Energy: " << energy << endl;
        cout << "Memory: " << mem << endl;
        cout << "Money: " << money << endl;
    }
};

class Player : public People {
private:
    vector<Item> inventory;

public:
    Player(string name, int health, int energy, int mem, int money)
        : People(name, health, energy, mem, money) {}

    void addItem(const Item& item) {
        inventory.push_back(item);
    }

    void removeItem(string itemName) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->getName() == itemName) {
                inventory.erase(it);
                return;
            }
        }
        cout << "Item not found in inventory!" << endl;
    }

    void useItem(string itemName) {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if (it->getName() == itemName) {
                cout << "Using item: " << itemName << endl;
                modifyStats(it->getHealthEffect(), it->getEnergyEffect(), 0, 0);
                inventory.erase(it);
                return;
            }
        }
        cout << "Item not found in inventory!" << endl;
    }

    void displayStats() const override {
        People::displayStats();
        cout << "Inventory: ";
        if (inventory.empty()) {
            cout << "No items." << endl;
        } else {
            for (const auto& item : inventory) {
                cout << item.getName() << " ";
            }
            cout << endl;
        }
    }
};

class NPC : public People {
private:
    vector<Event> events;

public:
    NPC(string name)
        : People(name, 50, 0, 0, 0) {}

    void addEvent(const Event& event) {
        events.push_back(event);
    }

    void triggerRandomEvent(Player& player) {
        if (!events.empty()) {
            int randomIndex = rand() % events.size();
            events[randomIndex].runEvent(player);
        } else {
            cout << name << " has no events to trigger." << endl;
        }
    }

    void displayStats() const override {
        cout << "Name: " << name << endl;
        cout << "Health: " << health << endl;
    }
};

    // void attack(Player& player) {
    //     int damage = rand() % 10 + 1;
    //     cout << name << " attacks " << player.getName() << " for " << damage << " damage!" << endl;
    //     player.modifyStats(-damage, 0, 0, 0);
    // }

    // void give(Player& player) {
    //     int itemOrMoney = rand() % 2;
    //     if (itemOrMoney == 0) {
    //         int amount = rand() % 20 + 1;
    //         cout << name << " gives " << amount << " money to " << player.getName() << "!" << endl;
    //         player.modifyStats(0, 0, 0, amount);
    //     } else {
    //         Item gift("Health Potion", 20, 0);
    //         cout << name << " gives a " << gift.getName() << " to " << player.getName() << "!" << endl;
    //         player.addItem(gift);
    //     }
    // }

    // void sendMessage() {
    //     vector<string> messages = {
    //         "Stay strong, traveler!",
    //         "Beware of the cave ahead.",
    //         "You can do it!",
    //         "Remember to rest."
    //     };
    //     int randomIndex = rand() % messages.size();
    //     cout << name << " says: \"" << messages[randomIndex] << "\"" << endl;
    // }