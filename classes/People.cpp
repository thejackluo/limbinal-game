using namespace std;
#include <string>
#include <vector>
#include "Item.cpp"
class People {
    public:
        People(string name, int health, int energy, int mem, int money): name(name), health(health), energy(energy), mem(mem), money(money) {}
        void setName(string name) {
            this->name = name;
        }
        string getName() {
            return name;
        }
        void setHealth(int health) {
            this->health = health;
        }
        int getHealth() {
            return health;
        }
        void setEnergy(int energy){
            this->energy = energy;
        }
        int getEnergy() {
            return energy;
        }
        void setMem(int mem) {
            this->mem = mem;
        }
        int getMem() {
            return mem;
        }
        void setMoney(int money) {
            this->money = money;
        }
        int getMoney() {
            return money;
        }
        // inventory items

    private:
        string name;
        int health;
        int energy;
        int mem;
        int money;
        vector <Item> inventory;
        // inventory items

};