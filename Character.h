//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_CHARACTER_H
#define CARLOSBADILLAARIAS_PROYECTO2_CHARACTER_H
#include "Entity.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Consumable.h"
#include "Objective.h"
#include <vector>
#include <map>
#include <memory>
#include <string>
using namespace std;

enum class Race { HUMAN, ELF, DWARF, MAGE, FAIRY };

class Character : public Entity {
private:
    Race race;
    string raceName;
    Inventory inventory;
    vector<shared_ptr<Objective>> objectives;
    map<string, int> stats;
    int experience;
    int level;
    int gold;
    shared_ptr<Weapon> equippedWeapon;

    void applyRaceBonuses();

public:
    Character(const string& name,Race race,int maxHealth = 100,int attackPower= 10, int defensePower = 5);

    Race getRace()const;
    string getRaceName()const;
    int getExperience()const;
    int getLevel()const;
    int getGold()const;
    int getStat(const string& s)const;

    Inventory& getInventory();
    shared_ptr<Weapon> getEquippedWeapon() const;
    int getEffectiveAttack() const;

    const vector<shared_ptr<Objective>>& getObjectives() const;

    void addGold(int amount);
    void addExperience(int amount);
    void addObjective(shared_ptr<Objective> obj);

    void pickUpItem(shared_ptr<Item> item);
    shared_ptr<Item> dropItem(const string& itemName);
    bool equipWeapon(const string& weaponName);
    bool useConsumable(const string& itemName);

    void update() override;
    void interact() override;
    string describe()const override;
    string getFullStatus()const;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j)override;
};
#endif //CARLOSBADILLAARIAS_PROYECTO2_CHARACTER_H
