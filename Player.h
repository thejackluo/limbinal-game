#ifndef PLAYER_H
#define PLAYER_H

#include "People.h"
#include "InventoryContainer.h"  // For InventoryContainer<T>
#include "Item.h"                // For Item and ItemType
// forward declare Location
class Location;

class Player : public People {
public:
    Player(std::string name, int health, int energy, int mem, int money);

    // Inventory methods
    void addItem(const Item& item);
    void removeItem(const Item& item);
    void useItem(const Item& item);
    void displayInventory() const;
    void sortInventoryById();
    void sortInventoryByName();

    // Stats methods
    void displayStats() const override;

    // Location methods (for movement)
    void setCurrentLocation(Location* location);
    Location* getCurrentLocation() const;

private:
    InventoryContainer<Item> inventory;
    Location* currentLocation;
};

#endif // PLAYER_H