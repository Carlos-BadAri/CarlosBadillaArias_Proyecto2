//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ENEMY_H
#define CARLOSBADILLAARIAS_PROYECTO2_ENEMY_H
#include "Entity.h"
#include "Item.h"
#include "ICombatStrategy.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;

class Enemy : public Entity {
private:
    string enemyType;
    bool isBoss;
    int experienceReward;
    unique_ptr<ICombatStrategy> strategy;
    vector<shared_ptr<Item>> rewards;

public:
    Enemy(const string& name, const string& description,int maxHealth, int attackPower, int defensePower,
        const string& enemyType, bool isBoss,int expReward, unique_ptr<ICombatStrategy> strategy);

    string getEnemyType() const;
    bool getIsBoss() const;
    int getExperienceReward()const;
    string getStrategyName() const;
    virtual int computeAttack() const;

    void addReward(shared_ptr<Item> item);
    virtual const vector<shared_ptr<Item>>& getRewards() const;
    virtual bool isDecorated() const;

    void update() override;
    void interact() override;
    string describe() const override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j)override;
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_ENEMY_H
