#include <iostream>
#include <string>
#include <vector>
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
    InventoryContainer<Item> inventory;

public:
    Player(string name, int health, int energy, int mem, int money)
        : People(name, health, energy, mem, money) {}

    void addItem(const Item& item) {
        inventory.addItem(item);
    }

    void removeItem(const Item& item) {
        inventory.removeItem(item);
    }

    void useItem(const Item& item) {
        if (inventory.contains(item)) {
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
            inventory.removeItem(item);
        } else {
            cout << "Item not found in inventory!" << endl;
        }
    }

    void displayStats() const override {
        People::displayStats();
        cout << "Inventory: ";
        inventory.displayItems();
    }

    void displayInventory() const {
        cout << "Inventory: ";
        inventory.displayItems();
    }

    void sortInventoryById() {
        inventory.sortItemsById();
    }

    void sortInventoryByName() {
        inventory.sortItemsByName();
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