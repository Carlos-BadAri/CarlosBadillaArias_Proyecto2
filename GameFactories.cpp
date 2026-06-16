//
// Created by carba on 10/6/2026.
//

#include "GameFactories.h"

using namespace std;

//MedievalItemFactory

shared_ptr<Item> MedievalItemFactory::createItem(const json& data) const {
    string type = data.value("type","consumable");
    string name = data.value("name","Unknown");
    string desc = data.value("description","");
    float w = data.value("weight",1.0f);
    int val = data.value("value",0);

    shared_ptr<Item> item;

    if (type == "weapon") {
        item = make_shared<Weapon>(name, desc, w, val,data.value("damage",5),
            data.value("attack_type", "slash"),data.value("durability",20));
    } else if (type == "consumable") {
        item = make_shared<Consumable>(name,desc, w,val,data.value("effect_amount",20),
            data.value("effect_type","heal"), data.value("uses",1));
    } else if (type == "key") {
        item = make_shared<KeyItem>(name, desc, w, val, data.value("unlocks", ""));
    } else {
        throw runtime_error("Tipo de objeto desconocido: " + type);
    }

    if (data.value("poisoned", false)) {
        item = make_shared<PoisonedItemDecorator>(item,data.value("poison_damage", 2));
    }

    return item;
}

//MedievalEnemyFactory

unique_ptr<ICombatStrategy>
MedievalEnemyFactory::buildStrategy(const string& name) const {
    if (name == "defensive") {
        return make_unique<DefensiveStrategy>();
    }
    if (name == "random") {
        return make_unique<RandomStrategy>();
    }
    return make_unique<AggressiveStrategy>();
}

shared_ptr<Enemy> MedievalEnemyFactory::createEnemy(const json& data) const {
    string stratName = data.value("strategy", "aggressive");

    auto enemy = make_shared<Enemy>(data.value("name","Unknown"),
        data.value("description",""),data.value("health",50),
        data.value("attack",8),data.value("defense",3),
        data.value("enemy_type","monster"),data.value("is_boss",false),
        data.value("experience",20),buildStrategy(stratName)
    );

    if (data.value("armored", false)) {
        return make_shared<ArmoredEnemyDecorator>(enemy,data.value("armor_bonus", 3));
    }
    if (data.value("enraged", false)) {
        return make_shared<EnragedEnemyDecorator>(enemy,data.value("rage_bonus", 4));
    }

    return enemy;
}