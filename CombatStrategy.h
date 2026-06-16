//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_COMBATSTRATEGY_H
#define CARLOSBADILLAARIAS_PROYECTO2_COMBATSTRATEGY_H

#include "ICombatStrategy.h"
#include <string>
using namespace std;

//I put these classes together because they are small

class Enemy;

class AggressiveStrategy : public ICombatStrategy {
public:
    int calculateAttack(const Enemy& enemy) const override;
    string getName() const override;
};

class DefensiveStrategy : public ICombatStrategy {
public:
    int calculateAttack(const Enemy& enemy) const override;
    string getName() const override;
};

class RandomStrategy : public ICombatStrategy {
public:
    int calculateAttack(const Enemy& enemy) const override;
    string getName() const override;
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_COMBATSTRATEGY_H
