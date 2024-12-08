#include "People.h"
#include <iostream>
#include <algorithm>

People::People(std::string name, int health, int energy, int mem, int money)
    : name(std::move(name)), health(health), energy(energy), mem(mem), money(money) {}

People::~People() {}

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

bool People::operator==(const People& other) const {
    return name == other.name;
}

void People::setName(std::string name) {
    this->name = std::move(name);
}

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
}

void People::displayStats() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Energy: " << energy << std::endl;
    std::cout << "Memory: " << mem << std::endl;
    std::cout << "Money: " << money << std::endl;
}