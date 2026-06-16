//
// Created by carba on 9/6/2026.
//
#include "EnemyDecorator.h"
using namespace std;

//EnemyDecorator

EnemyDecorator::EnemyDecorator(shared_ptr<Enemy> enemy,unique_ptr<ICombatStrategy> strategy) : Enemy(enemy->getName(),
    enemy->getDescription(),enemy->getMaxHealth(), enemy->getAttackPower(),enemy->getDefensePower(), enemy->getEnemyType(),
    enemy->getIsBoss(), enemy->getExperienceReward(),move(strategy)),wrapped(enemy) {
    this->currentHealth = enemy->getCurrentHealth();
    this->alive = enemy->isAlive();
}

bool EnemyDecorator::isDecorated() const {
    return true;
}

const vector<shared_ptr<Item>>& EnemyDecorator::getRewards() const {
    return wrapped->getRewards();
}

string EnemyDecorator::describe() const {
    string bossTag = getIsBoss() ? " [Jefe]" : "";
    return getEnemyType() + bossTag + " '" + getName() + "'"+ " HP:" + to_string(getCurrentHealth()) + "/" + to_string(getMaxHealth())+ " ATK:" + to_string(getAttackPower())+ " DEF:" + to_string(getDefensePower())+ " [" + getStrategyName() + "]";
}

//ArmoredEnemyDecorator

ArmoredEnemyDecorator::ArmoredEnemyDecorator(shared_ptr<Enemy> enemy,int extraDefense): EnemyDecorator(enemy,
    make_unique<AggressiveStrategy>()),extraDefense(extraDefense) {
    defensePower += extraDefense;
}

string ArmoredEnemyDecorator::describe() const {
    string bossTag = getIsBoss() ? " [Jefe]" : "";
    return getEnemyType() + bossTag + " '" + getName() + "'"+ " HP:" + to_string(getCurrentHealth()) + "/" + to_string(getMaxHealth())+ " ATK:" + to_string(getAttackPower())+ " DEF:" + to_string(getDefensePower())+ " [" + getStrategyName() + "]"+ " [Armadura +" + to_string(extraDefense) + "DEF]";
}

//EnragedEnemyDecorator

EnragedEnemyDecorator::EnragedEnemyDecorator(shared_ptr<Enemy> enemy,int extraAttack) : EnemyDecorator(enemy,
    make_unique<AggressiveStrategy>()),extraAttack(extraAttack) {
    attackPower += extraAttack;
}

int EnragedEnemyDecorator::computeAttack() const {
    return Enemy::computeAttack();
}

string EnragedEnemyDecorator::describe() const {
    string bossTag = getIsBoss() ? " [Jefe]" : "";
    return getEnemyType() + bossTag + " '" + getName() + "'"+ " HP:" + to_string(getCurrentHealth()) + "/" + to_string(getMaxHealth())+ " ATK:" + to_string(getAttackPower())+ " DEF:" + to_string(getDefensePower())+ " [" + getStrategyName() + "]"+ " [Enfurecido +" + to_string(extraAttack) + "ATK]";
}