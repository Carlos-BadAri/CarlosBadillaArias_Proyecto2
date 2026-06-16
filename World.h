//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_WORLD_H
#define CARLOSBADILLAARIAS_PROYECTO2_WORLD_H
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Space.h"
#include "Character.h"
#include "Enemy.h"
#include "Objective.h"
#include "ISerializable.h"
using namespace std;

class World : public ISerializable {
private:
    string worldName;
    string theme;
    string bossFinalName;

    vector<shared_ptr<Zone>>zones;
    vector<Space*>allSpaces;
    vector<shared_ptr<Enemy>>enemies;
    shared_ptr<CompositeObjective> mainQuest;

    shared_ptr<Character> player;
    Space* currentSpace;
    int currentTurn;
    bool adventureComplete;
    bool playerWon;

public:
    World(const string& worldName, const string& theme);

    string getWorldName()const;
    string getTheme()const;
    string getBossFinalName()const;

    shared_ptr<Character>getPlayer()const;
    Space* getCurrentSpace()const;
    int getCurrentTurn()const;
    bool isComplete() const;
    bool getPlayerWon()const;

    shared_ptr<CompositeObjective>getMainQuest()const;
    const vector<shared_ptr<Enemy>>& getEnemies() const;
    const vector<Space*>& getAllSpaces() const;
    const vector<shared_ptr<Zone>>& getZones()const;

    void setBossFinalName(const string& n);
    void setPlayer(shared_ptr<Character> c);
    void setStartingSpace(const string& spaceId);
    void advanceTurn();
    void setComplete(bool won);

    void addZone(shared_ptr<Zone> zone);
    void addEnemy(shared_ptr<Enemy> e);
    void addObjective(shared_ptr<Objective> obj);

    Space* findSpace(const string& id)const;
    shared_ptr<Enemy> findEnemy(const string& name) const;

    bool movePlayer(const string& direction);
    void checkObjectives();

    nlohmann::json toJson()const override;
    void fromJson(const nlohmann::json& j)override;
};
#endif //CARLOSBADILLAARIAS_PROYECTO2_WORLD_H
