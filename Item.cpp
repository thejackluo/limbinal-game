using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

enum class ItemType {
    HEALTH,
    ENERGY,
    MEM,
    MONEY
};

class Item {
public:
    Item(int id, string name, ItemType type, int value)
        : id(id), name(name), type(type), value(value) {}

    int getId() const { return id; }
    string getName() const { return name; }
    ItemType getType() const { return type; }
    int getValue() const { return value; }

    void setType(ItemType type) { this->type = type; }
    void setValue(int value) { this->value = value; }

    void display() const {
        cout << "Item ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << itemTypeToString(type) << endl;
        cout << "Value: " << value << endl;
    }

    bool operator==(const Item& other) const {
        return id == other.id && name == other.name && type == other.type && value == other.value;
    }

private:
    int id;
    string name;
    ItemType type;
    int value;

    string itemTypeToString(ItemType type) const {
        switch (type) {
            case ItemType::HEALTH: return "Health";
            case ItemType::ENERGY: return "Energy";
            case ItemType::MEM: return "Memory";
            case ItemType::MONEY: return "Money";
            default: return "Unknown";
        }
    }
};

template <typename T>
class InventoryContainer {
public:
    void addItem(const T& item) {
        items.push_back(item);
    }

    void removeItem(const T& item) {
        auto it = std::find(items.begin(), items.end(), item);
        if (it != items.end()) {
            items.erase(it);
        } else {
            std::cout << "Item not found in inventory!" << std::endl;
        }
    }

    void displayItems() const {
        if (items.empty()) {
            std::cout << "No items in inventory." << std::endl;
        } else {
            for (const auto& item : items) {
                item.display();
            }
        }
    }

    void sortItemsById() {
        std::sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getId() < b.getId();
        });
    }

    void sortItemsByName() {
        std::sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getName() < b.getName();
        });
    }

    bool contains(const T& item) const {
        return std::find(items.begin(), items.end(), item) != items.end();
    }

private:
    std::vector<T> items;
};