//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_WEPON_H
#define CARLOSBADILLAARIAS_PROYECTO2_WEPON_H
#include "Item.h"
#include <string>
using namespace std;

class Weapon : public Item{
private:
    int damage;
    string attackType;
    int durability;

public:
    Weapon(const string& name, const string& description,float weight, int value,int demage, const string& attackType, int durability);
    int getDamage() const;
    string getAttackType() const;
    int getDurability() const;

    string getCategory()const override;
    string getType()const override;
    void use() override;
    string describe() const override;

    nlohmann::json toJson()const override;
    void fromJson(const nlohmann::json& json) override;
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_WEPON_H
