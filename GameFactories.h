//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_GAMEFACTORIES_H
#define CARLOSBADILLAARIAS_PROYECTO2_GAMEFACTORIES_H
#include <string>
#include <memory>
#include <stdexcept>
#include "Item.h"
#include "Weapon.h"
#include "Consumable.h"
#include "KeyItem.h"
#include "Enemy.h"
#include "CombatStrategy.h"
#include "ItemDecorator.h"
#include "EnemyDecorator.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class IItemFactory {
public:
    virtual shared_ptr<Item> createItem(const json& data) const = 0;
    virtual ~IItemFactory() = default;
};

class IEnemyFactory {
public:
    virtual shared_ptr<Enemy> createEnemy(const json& data) const = 0;
    virtual ~IEnemyFactory() = default;
};

class MedievalItemFactory : public IItemFactory {
public:
    shared_ptr<Item> createItem(const json& data) const override;
};

class MedievalEnemyFactory : public IEnemyFactory {
private:
    unique_ptr<ICombatStrategy> buildStrategy(const string& name) const;

public:
    shared_ptr<Enemy> createEnemy(const json& data) const override;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_GAMEFACTORIES_H
