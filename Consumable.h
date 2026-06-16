//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_CONSUMABLE_H
#define CARLOSBADILLAARIAS_PROYECTO2_CONSUMABLE_H
#include "Item.h"
#include <string>
using namespace std;

class Consumable : public Item {
private:
    int effectAmount;
    string effectType;
    int uses;

public:
    Consumable(const string& name, const string& description, float weight, int value, int effectAmount, const string& effectType, int uses = 1);
    int getEffectAmount()const;
    string getEffectType()const;
    int getUses()const;
    string getCategory() const override;
    string getType() const override;
    void use() override;
    string describe() const override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json &j) override;
};
#endif //CARLOSBADILLAARIAS_PROYECTO2_CONSUMABLE_H
