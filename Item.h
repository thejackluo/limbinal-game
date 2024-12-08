#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>

enum class ItemType {
    HEALTH,
    ENERGY,
    MEM,
    MONEY
};

class Item {
public:
    Item(int id, const std::string& name, ItemType type, int value);

    int getId() const;
    std::string getName() const;
    ItemType getType() const;
    int getValue() const;

    void setType(ItemType type);
    void setValue(int value);

    void display() const;

    bool operator==(const Item& other) const;

private:
    int id;
    std::string name;
    ItemType type;
    int value;

    std::string itemTypeToString(ItemType type) const;
};

#endif // ITEM_H