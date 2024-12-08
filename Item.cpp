#include "Item.h"

Item::Item(int id, const std::string& name, ItemType type, int value)
    : id(id), name(name), type(type), value(value) {}

int Item::getId() const {
    return id;
}

std::string Item::getName() const {
    return name;
}

ItemType Item::getType() const {
    return type;
}

int Item::getValue() const {
    return value;
}

void Item::setType(ItemType type) {
    this->type = type;
}

void Item::setValue(int value) {
    this->value = value;
}

void Item::display() const {
    std::cout << "Item ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Type: " << itemTypeToString(type) << std::endl;
    std::cout << "Value: " << value << std::endl;
}

bool Item::operator==(const Item& other) const {
    return id == other.id && name == other.name && type == other.type && value == other.value;
}

std::string Item::itemTypeToString(ItemType type) const {
    switch (type) {
        case ItemType::HEALTH: return "Health";
        case ItemType::ENERGY: return "Energy";
        case ItemType::MEM:    return "Memory";
        case ItemType::MONEY:  return "Money";
        default:               return "Unknown";
    }
}