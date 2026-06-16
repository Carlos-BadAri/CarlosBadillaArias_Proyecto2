//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ENEMYDECORATOR_H
#define CARLOSBADILLAARIAS_PROYECTO2_ENEMYDECORATOR_H
#include "Enemy.h"
#include "CombatStrategy.h"
#include <memory>
#include <string>
using namespace std;

class EnemyDecorator : public Enemy {
protected:
    shared_ptr<Enemy> wrapped;

public:
    EnemyDecorator(shared_ptr<Enemy> enemy,unique_ptr<ICombatStrategy> strategy);
    bool isDecorated() const override;
    const vector<shared_ptr<Item>>& getRewards() const override;
    string describe() const override;
};

class ArmoredEnemyDecorator : public EnemyDecorator {
private:
    int extraDefense;
public:
    ArmoredEnemyDecorator(shared_ptr<Enemy> enemy, int extraDefense);
    string describe() const override;
};

class EnragedEnemyDecorator : public EnemyDecorator {
private:
    int extraAttack;
public:
    EnragedEnemyDecorator(shared_ptr<Enemy> enemy, int extraAttack);
    int computeAttack() const override;
    string describe() const override;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_ENEMYDECORATOR_H
