#ifndef PEOPLE_H
#define PEOPLE_H

#include <string>

class People {
public:
    People(std::string name, int health, int energy, int mem, int money);
    virtual ~People();

    People& operator=(const People& other);
    bool operator==(const People& other) const;

    void setName(std::string name);
    std::string getName() const;

    void modifyStats(int healthChange, int energyChange, int memChange, int moneyChange);

    virtual void displayStats() const;

protected:
    std::string name;
    int health;
    int energy;
    int mem;
    int money;
};

#endif // PEOPLE_H