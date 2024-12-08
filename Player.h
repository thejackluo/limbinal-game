#ifndef PLAYER_H
#define PLAYER_H

#include "People.h"
#include "InventoryContainer.h"  // For InventoryContainer<T>
#include "Item.h"                // For Item and ItemType
#include "Location.h"            // For Location

class Player : public People {
public:
    Player(std::string name, int health, int energy, int mem, int money);

    void addItem(const Item& item);
    void removeItem(const Item& item);
    void useItem(const Item& item);

    void displayStats() const override;
    void displayInventory() const;
    void sortInventoryById();
    void sortInventoryByName();

    void setCurrentLocation(Location* location);
    Location* getCurrentLocation() const;

private:
    InventoryContainer<Item> inventory;
    Location* currentLocation;
};

#endif // PLAYER_H