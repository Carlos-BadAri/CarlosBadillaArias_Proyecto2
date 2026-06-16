//
// Created by carba on 8/6/2026.
//

#include "Entity.h"

using namespace std;

Entity::Entity(const string& name, const string& description,int maxHealth, int attackPower, int defensePower): name(name),
    description(description),currentHealth(maxHealth), maxHealth(maxHealth),attackPower(attackPower), defensePower(defensePower),alive(true) {
}

string Entity::getName() const {
    return name;
}

string Entity::getDescription() const {
    return description;
}

int Entity::getMaxHealth() const {
    return maxHealth;
}

int Entity::getCurrentHealth() const {
    return currentHealth;
}

int Entity::getAttackPower() const {
    return attackPower;
}

int Entity::getDefensePower() const {
    return defensePower;
}

bool Entity::isAlive() const {
    return alive;
}

void Entity::setName(const string& name) {
    this->name = name;
}

void Entity::takeDamage(int damage) {
    int actual = damage - defensePower;
    if (actual < 1) {
        actual = 1;
    }
    currentHealth -= actual;
    if (currentHealth <= 0) {
        currentHealth = 0;
        alive = false;
    }
}

void Entity::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
    if (currentHealth > 0) {
        alive = true;
    }
}