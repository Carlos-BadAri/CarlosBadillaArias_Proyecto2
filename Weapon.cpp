//
// Created by carba on 9/6/2026.
//

#include "Weapon.h"

Weapon::Weapon(const string& name, const string& description,float weight, int value,int damage, const string& attackType, int durability):
Item(name, description, weight, value), damage(damage), attackType(attackType), durability(durability) {

}

int Weapon::getDamage() const {
    return damage;
}

string Weapon::getAttackType() const {
    return attackType;
}

int Weapon::getDurability() const {
    return durability;
}

string Weapon::getCategory() const {
    return "weapon";
}

string Weapon::getType() const {
    return "Weapon";
}

void Weapon::use() {
    if (durability > 0) {
        durability--;
    }
}

string Weapon::describe() const {
    return "[Arma]" +name+"|DMG:"+to_string(damage)+"|"+attackType+"| DUR:"+to_string(durability);
}

nlohmann::json Weapon::toJson() const {
    return {{"type","weapon"},{"name",name},{"description", description},{"weight",weight},
        {"value",value},{"damage",damage},{"attack type",attackType},{"durability",durability}
    };
}

void Weapon::fromJson(const nlohmann::json &j) {
    damage = j.value("damage",5);
    attackType = j.value("attackType", "slash");
    durability = j.value("durability", 20);
}
