#ifndef INVENTORYCONTAINER_H
#define INVENTORYCONTAINER_H

#include <vector>
#include <algorithm>
#include <iostream>

// Forward declare Item if needed, but usually including Item.h is fine if you need item details.
// #include "Item.h" // If you need Item here, you can include it.
// This template class works for any type T that provides the required interface (like Item).
// If you plan to use it specifically for Item objects, you may #include "Item.h".
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

#endif 