//
// Created by carba on 8/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ENTITY_H
#define CARLOSBADILLAARIAS_PROYECTO2_ENTITY_H
#include <string>
#include "IInteractable.h"
#include "IUpdatable.h"
#include "ISerializable.h"

using namespace std;

class Entity : public IInteractable, public IUpdatable, public ISerializable {
protected:
    string name;
    string description;
    int currentHealth;
    int maxHealth;
    int attackPower;
    int defensePower;
    bool alive;

public:
    Entity(const string& name, const string& description,int maxHealth, int attackPower, int defensePower);
    virtual ~Entity() = default;

    string getName() const;
    string getDescription() const;
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getAttackPower() const;
    int getDefensePower() const;
    bool isAlive() const;

    void setName(const string& name);
    void takeDamage(int damage);
    void heal(int amount);

    virtual void update() = 0;
    virtual void interact() = 0;
    virtual string describe() const = 0;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_ENTITY_H
