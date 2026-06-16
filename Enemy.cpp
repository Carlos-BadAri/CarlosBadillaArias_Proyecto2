//
// Created by carba on 9/6/2026.
//

#include "Enemy.h"

using namespace std;

Enemy::Enemy(const string& name, const string& description,int maxHealth, int attackPower, int defensePower,
    const string& enemyType, bool isBoss,int expReward, unique_ptr<ICombatStrategy> strategy): Entity(name, description,
        maxHealth, attackPower, defensePower),enemyType(enemyType), isBoss(isBoss),experienceReward(expReward), strategy(move(strategy)) {
}

string Enemy::getEnemyType() const {
    return enemyType;
}
bool Enemy::getIsBoss() const {
    return isBoss;
}
int Enemy::getExperienceReward() const {
    return experienceReward;
}
string Enemy::getStrategyName() const {
    return strategy->getName();
}

int Enemy::computeAttack()const {
    return strategy->calculateAttack(*this);
}

void Enemy::addReward(shared_ptr<Item> item) {
    rewards.push_back(item);
}

const vector<shared_ptr<Item>>& Enemy::getRewards() const {
    return rewards;
}

bool Enemy::isDecorated() const {
    return false;
}

void Enemy::update() {
    if (strategy->getName() == "defensivo" && alive && currentHealth < maxHealth) {
        currentHealth++;
    }
}

void Enemy::interact() {
}

string Enemy::describe() const {
    string bossTag = isBoss ? " [Jefe]" : "";
    return enemyType + bossTag + " '" + name + "'" + " HP:" + to_string(currentHealth) + "/" + to_string(maxHealth)+
        " ATK:" + to_string(attackPower)+ " DEF:" + to_string(defensePower)+ "[" + strategy->getName() + "]";
}

nlohmann::json Enemy::toJson() const {
return {{"Nombre",name},{"Descripcion",description},{"salud",maxHealth},{"ataque",attackPower},{"defensa",defensePower},{"tipoEnemigo",enemyType},{"EsJefe",isBoss},{"Experiencia",experienceReward},{"Strategia",strategy->getName()}
    };
}

void Enemy::fromJson(const nlohmann::json&) {
}