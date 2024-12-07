using namespace std;
#include <string>

enum class ItemType {
    HEALTH,
    ENERGY,
    MEM,
    MONEY
};

class Item {
    public:
        Item (int id, string name, ItemType type, int value): id(id), name(name), type(type), value(value) {}
        int getId() const { return id; }
        string getName() const { return name; }
        ItemType getType() const { return type; }
        int getValue() const { return value; }
        void setType(ItemType type) { this->type = type; }
        void setValue(int value) { this->value = value; }

    private:
        int id;
        string name;
        ItemType type;
        int value;
};