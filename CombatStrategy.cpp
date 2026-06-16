//
// Created by carba on 9/6/2026.
//
#include "CombatStrategy.h"
#include "Enemy.h"
#include <cstdlib>

using namespace std;

int AggressiveStrategy::calculateAttack(const Enemy& enemy) const {
    return enemy.getAttackPower() + (rand() % 6 + 2);
}

string AggressiveStrategy::getName() const {
    return "agresivo";
}

int DefensiveStrategy::calculateAttack(const Enemy& enemy) const {
    return enemy.getAttackPower() + (rand() % 3);
}

string DefensiveStrategy::getName() const {
    return "defensivo";
}

int RandomStrategy::calculateAttack(const Enemy& enemy) const {
    int roll = rand() % 3;
    if (roll == 0) return enemy.getAttackPower() / 2;
    if (roll == 1) return enemy.getAttackPower();
    return enemy.getAttackPower() * 2;
}

string RandomStrategy::getName() const {
    return "impredecible";
}