//
// Created by carba on 9/6/2026.
//

#include "Character.h"
#include <iostream>
using namespace std;

void Character::applyRaceBonuses() {
    switch (race) {
        case Race::HUMAN:
            stats["strength"]=5; stats["agility"]=5;
            stats["magic"]=2;stats["luck"]=5;
            break;
        case Race::ELF:
            stats["strength"]=4; stats["agility"]=9;
            stats["magic"]=5; stats["luck"]=4;
            attackPower += 3;
            break;
        case Race::DWARF:
            stats["strength"]=9; stats["agility"]=2;
            stats["magic"]=1; stats["luck"]=3;
            defensePower+= 4;
            maxHealth += 20;
            currentHealth += 20;
            break;
        case Race::MAGE:
            stats["strength"]=3; stats["agility"]=4;
            stats["magic"]=10; stats["luck"]=4;
            attackPower += 6;
            break;
        case Race::FAIRY:
            stats["strength"]=3; stats["agility"]=10;
            stats["magic"]=7; stats["luck"]=9;
            attackPower+= 3;
            maxHealth -= 10;
            currentHealth -= 10;
            break;
    }
}

Character::Character(const string& name, Race race,int maxHealth, int attackPower, int defensePower) : Entity(name, "The adventurer", maxHealth, attackPower, defensePower),
      race(race), inventory(15, 100.0f), experience(0), level(1), gold(0), equippedWeapon(nullptr) {
    switch (race) {
        case Race::HUMAN:
            raceName = "Humano";
            break;
        case Race::ELF:
            raceName = "Elfo";
            break;
        case Race::DWARF:
            raceName = "Enano";
            break;
        case Race::MAGE:
            raceName = "Mago";
            break;
        case Race::FAIRY:
            raceName = "Hada";
            break;
    }
    applyRaceBonuses();
}

Race Character::getRace() const {
    return race;
}
string Character::getRaceName() const {
    return raceName;
}
int Character::getExperience() const {
    return experience;
}
int Character::getLevel() const {
    return level;
}
int Character::getGold() const {
    return gold;
}

int Character::getStat(const string& s) const {
    auto it = stats.find(s);
    return it != stats.end() ? it->second : 0;
}

Inventory& Character::getInventory() {
    return inventory;
}

shared_ptr<Weapon> Character::getEquippedWeapon() const {
    return equippedWeapon;
}

int Character::getEffectiveAttack() const {
    if (!equippedWeapon) return attackPower;

    shared_ptr<Weapon> w = dynamic_pointer_cast<Weapon>(equippedWeapon);
    if (w) return attackPower + w->getDamage();

    for (int i = 0; i < inventory.getSize(); i++) {
        shared_ptr<Weapon> inner = dynamic_pointer_cast<Weapon>(inventory[i]);
        if (inner && inner->getName() == equippedWeapon->getName()) {
            return attackPower + inner->getDamage();
        }
    }
    return attackPower;
}

const vector<shared_ptr<Objective>>& Character::getObjectives() const {
    return objectives;
}

void Character::addGold(int amount) {
    gold += amount;
}

void Character::addExperience(int amount) {
    experience += amount;
    if (experience >= level * 100) {
        level++;
        maxHealth += 10;
        currentHealth += 10;
        attackPower += 2;
        defensePower += 1;
        cout << "*** Subiste de nivel! Ahora eres nivel " << level << " ***\n";
    }
}

void Character::addObjective(shared_ptr<Objective> obj) {
    objectives.push_back(obj);
}

void Character::pickUpItem(shared_ptr<Item> item) {
    inventory.add(item);
}

shared_ptr<Item> Character::dropItem(const string& itemName) {
    return inventory.remove(itemName);
}

bool Character::equipWeapon(const string& weaponName) {
    shared_ptr<Item> found = inventory.find(weaponName);
    if (!found) return false;

    // Try to cast directly to Weapon
    shared_ptr<Weapon> w = dynamic_pointer_cast<Weapon>(found);

    // If it's a decorator, look for the Weapon inside
    if (!w && found->getCategory() == "weapon") {
        //Made a weapon using the decorated item's data
        equippedWeapon = make_shared<Weapon>(found->getName(),found->getDescription(),found->getWeight(),found->getValue(),0,"unknown",0);
        equippedWeapon = w;
    }

    if (!w) return false;
    equippedWeapon = w;
    return true;
}

bool Character::useConsumable(const string& itemName) {
    shared_ptr<Item> found = inventory.find(itemName);
    if (!found) {
        return false;
    }
    if (found->getCategory() != "consumable") {
        return false;
    }

    shared_ptr<Consumable> c = static_pointer_cast<Consumable>(found);
    if (c->getUses() <= 0) {
        return false;
    }

    if(c->getEffectType() == "heal") {
        heal(c->getEffectAmount());
    }else if (c->getEffectType() == "boost_attack") {
        attackPower  += c->getEffectAmount();
    }else if (c->getEffectType() == "boost_defense") defensePower += c->getEffectAmount();

    c->use();
    if (c->getUses() <= 0) {
        try {
            inventory.remove(itemName);
        } catch (...) {

        }
    }
    return true;
}

void Character::update() {

}
void Character::interact() {

}

string Character::describe() const {
    return raceName + " '" + name + "'" + " hp:"  + to_string(currentHealth) + "/" + to_string(maxHealth)+ " atk:" + to_string(getEffectiveAttack())
         + " def:" + to_string(defensePower) + " lvl:" + to_string(level);
}

string Character::getFullStatus() const {
    string s;
    s += "=== Estado del personaje ===\n";
    s += "Nombre: " + name + "\n";
    s += "Raza: " + raceName + "\n";
    s += "Nivel: " + to_string(level) + "  (EXP:" + to_string(experience) + ")\n";
    s += "HP: " + to_string(currentHealth) + "/" + to_string(maxHealth) + "\n";
    s += "ATK: " + to_string(getEffectiveAttack()) + "\n";
    s += "DEF: " + to_string(defensePower) + "\n";
    s += "Oro: " + to_string(gold) + "\n";
    s += "Arma: " + (equippedWeapon ? equippedWeapon->getName() : "ninguna") + "\n";
    s += "Fue=" + to_string(getStat("strength"))
       + " Agi=" + to_string(getStat("agility"))
       + " Mag=" + to_string(getStat("magic"))
       + " Sue=" + to_string(getStat("luck")) + "\n";
    return s;
}

nlohmann::json Character::toJson() const {
    return {{"name",name},{"race",raceName},{"level",level},{"experience",experience},{"health",currentHealth},{"maxHealth",maxHealth},{"gold",gold}};
}

void Character::fromJson(const nlohmann::json&) {

}
