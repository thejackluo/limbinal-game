#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

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

    virtual ~People() {}

    People& operator=(const People& other) {
        if (this != &other) {
            name = other.name;
            health = other.health;
            energy = other.energy;
            mem = other.mem;
            money = other.money;
        }
        return *this;
    }

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

    void removeItem(const Item& item) {
        auto it = std::find(inventory.begin(), inventory.end(), item);
        if (it != inventory.end()) {
            inventory.erase(it);
        } else {
            cout << "Item not found in inventory!" << endl;
        }
    }

    void useItem(const Item& item) {
        auto it = std::find(inventory.begin(), inventory.end(), item);
        if (it != inventory.end()) {
            cout << "Using item: " << item.getName() << endl;
            switch (item.getType()) {
                case ItemType::HEALTH:
                    modifyStats(item.getValue(), 0, 0, 0);
                    break;
                case ItemType::ENERGY:
                    modifyStats(0, item.getValue(), 0, 0);
                    break;
                case ItemType::MEM:
                    modifyStats(0, 0, item.getValue(), 0);
                    break;
                case ItemType::MONEY:
                    modifyStats(0, 0, 0, item.getValue());
                    break;
                default:
                    break;
            }
            inventory.erase(it);
        } else {
            cout << "Item not found in inventory!" << endl;
        }
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

    void sortInventoryById() {
        sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
            return a.getId() < b.getId();
        });
    }

    void sortInventoryByName() {
        sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
            return a.getName() < b.getName();
        });
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

// Archived code
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