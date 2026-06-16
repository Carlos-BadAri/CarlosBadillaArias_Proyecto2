//
// Created by carba on 9/6/2026.
//

#include "Consumable.h"

Consumable::Consumable(const string &name, const string &description, float weight, int value, int effectAmount,
    const string &effectType, int uses) : Item(name,description,weight,value), effectAmount(effectAmount), effectType(effectType), uses(uses) {
}

int Consumable::getEffectAmount() const {
    return effectAmount;
}

string Consumable::getEffectType() const {
    return effectType;
}

int Consumable::getUses() const {
    return uses;
}

string Consumable::getCategory() const {
    return "consumable";
}

string Consumable::getType() const {
    return "Consumable";
}

void Consumable::use() {
    if (uses>0) {
        uses--;
    }
}

string Consumable::describe() const {
    return Item::describe();
}

nlohmann::json Consumable::toJson() const {
    return {{"type", "consumable"},{"name",name},{"description", description},
        {"weight", weight},{"value",value},{"effectAmaunt", effectAmount}};
}

void Consumable::fromJson(const nlohmann::json &j) {
    effectAmount = j.value("effectAmount", 20);
    effectType = j.value("effectType", "heal");
    uses = j.value("uses", 1);
}
