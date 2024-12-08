#include "People.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

People::People(std::string name, int health, int energy, int mem, int money)
    : name(std::move(name)), health(health), energy(energy), mem(mem), money(money) {}

People::~People() {}

// Assignment operator
People& People::operator=(const People& other) {
    if (this != &other) {
        name = other.name;
        health = other.health;
        energy = other.energy;
        mem = other.mem;
        money = other.money;
    }
    return *this;
}

// Equality operator
bool People::operator==(const People& other) const {
    return name == other.name;
}

// Set the name of the person
void People::setName(std::string name) {
    this->name = std::move(name);
}

// Get the name of the person
std::string People::getName() const {
    return name;
}

void People::modifyStats(int healthChange, int energyChange, int memChange, int moneyChange) {
    health += healthChange;
    energy += energyChange;
    mem += memChange;
    money += moneyChange;
    if (health < 0) health = 0;
    if (energy < 0) energy = 0;
    if (money < 0) money = 0;

    // Write out a log message with one line for each stat that was changed
    if (healthChange != 0) std::cout << "Health changed by " << healthChange << std::endl;
    if (energyChange != 0) std::cout << "Energy changed by " << energyChange << std::endl;
    if (memChange != 0) std::cout << "Memory changed by " << memChange << std::endl;
    if (moneyChange != 0) std::cout << "Money changed by " << moneyChange << std::endl;

    // if health is 0, the person is dead
    if (health == 0) {
        std::cout << name << " has died." << std::endl;
    }

    // if energy is 0, the person is exhausted (please eat food or drink energy drinks)
    if (energy == 0) {
        std::cout << name << " is exhausted. Please eat food or drink energy drinks." << std::endl;
    }
}

void People::displayStats() const {
    // Helper function to create progress bars
    auto createProgressBar = [](int value, int maxValue = 100, int barWidth = 20) {
        int filled = (value * barWidth) / maxValue;
        std::string bar = "[";
        for (int i = 0; i < barWidth; ++i) {
            if (i < filled) {
                bar += "="; // Filled part
            } else {
                bar += " "; // Empty part
            }
        }
        bar += "] " + std::to_string(value) + "/" + std::to_string(maxValue);
        return bar;
    };

    // Display stats
    std::cout << "=============================================" << std::endl;
    std::cout << "STATS: " << name << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    // Health
    std::cout << "Health: " << createProgressBar(health) << std::endl;

    // Energy
    std::cout << "Energy: " << createProgressBar(energy) << std::endl;

    // Memory
    std::cout << "Memory: " << createProgressBar(mem) << std::endl;

    // Money
    std::cout << "Money: $" << money << std::endl;
    std::cout << "=============================================" << std::endl;
}
