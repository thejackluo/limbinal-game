#include "Player.h"
#include <iostream>

Player::Player(std::string name, int health, int energy, int mem, int money)
    : People(std::move(name), health, energy, mem, money), currentLocation(nullptr) {}

Player::Player(const Player& other)
    : People(other), inventory(other.inventory), currentLocation(other.currentLocation) {}

void Player::addItem(const Item& item) { inventory.addItem(item);}

void Player::removeItem(const Item& item) { inventory.removeItem(item);}

void Player::useItem(const Item& item) {
    if (inventory.contains(item)) {
        std::cout << "Using item: " << item.getName() << std::endl;
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
        std::cout << "Item not found in inventory!" << std::endl;
    }
}

void Player::displayStats() const { People::displayStats(); std::cout << "Inventory: "; inventory.displayItems(); }
void Player::displayInventory() const { std::cout << "Inventory: "; inventory.displayItems(); }
void Player::sortInventoryById() { inventory.sortItemsById(); }
void Player::sortInventoryByName() { inventory.sortItemsByName(); }
void Player::setCurrentLocation(Location* location) { currentLocation = location; }
Location* Player::getCurrentLocation() const { return currentLocation; }