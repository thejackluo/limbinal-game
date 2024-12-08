#include "Item.h"

Item::Item(int id, const std::string& name, ItemType type, int value)
    : id(id), name(name), type(type), value(value) {}

// Getter functions
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

// Setter functions
void Item::setType(ItemType type) {
    this->type = type;
}

void Item::setValue(int value) {
    this->value = value;
}

// Display function
void Item::display() const {
    // Generate the description dynamically
    std::string description;
    if (value > 0) {
        description = "Increases your " + itemTypeToString(type) + " by " + std::to_string(value);
    } else if (value < 0) {
        description = "Decreases your " + itemTypeToString(type) + " by " + std::to_string(-value);
    } else {
        description = "Does not affect your " + itemTypeToString(type);
    }

    int minBoxWidth = 60; // Minimum box width
    int contentWidth = std::max<int>(name.length() + 6, description.length() + 6);
    int boxWidth = std::max(minBoxWidth, contentWidth); 

    // Top border (ASCII)
    std::cout << "+" << std::string(boxWidth, '-') << "+\n";

    // Title line: [ID]. Name
    std::string title = "[" + std::to_string(id) + "]. " + name;
    std::cout << "| " << std::left << std::setw(boxWidth - 2) << title << "|\n";

    // Description line
    std::string descLine = "Desc: " + description;
    std::cout << "| " << std::left << std::setw(boxWidth - 2) << descLine << "|\n";

    // Bottom border
    std::cout << "+" << std::string(boxWidth, '-') << "+\n";
}

// Operator overloading
bool Item::operator==(const Item& other) const {
    return id == other.id && name == other.name && type == other.type && value == other.value;
}

// Helper function to convert ItemType to string
std::string Item::itemTypeToString(ItemType type) const {
    switch (type) {
        case ItemType::HEALTH: return "Health";
        case ItemType::ENERGY: return "Energy";
        case ItemType::MEM:    return "Memory";
        case ItemType::MONEY:  return "Money";
        default:               return "Unknown";
    }
}