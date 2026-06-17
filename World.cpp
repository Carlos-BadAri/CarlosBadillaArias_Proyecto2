//
// Created by carba on 10/6/2026.
//

#include "World.h"
#include <iostream>
using namespace std;

World::World(const string& worldName, const string& theme): worldName(worldName),
        theme(theme),currentSpace(nullptr), currentTurn(0),adventureComplete(false), playerWon(false) {
    mainQuest = make_shared<CompositeObjective>("main_quest", "Complete the adventure");
}

string World::getWorldName()const {
    return worldName;
}
string World::getTheme() const {
    return theme;
}
string World::getBossFinalName() const {
    return bossFinalName;
}

shared_ptr<Character> World::getPlayer()const {
    return player;
}
Space*  World::getCurrentSpace() const {
    return currentSpace;
}
int World::getCurrentTurn() const {
    return currentTurn;
}
bool World::isComplete()const {
    return adventureComplete;
}
bool World::getPlayerWon()const {
    return playerWon;
}

shared_ptr<CompositeObjective> World::getMainQuest() const {
    return mainQuest;
}
const vector<shared_ptr<Enemy>>& World::getEnemies() const {
    return enemies;
}
const vector<Space*>& World::getAllSpaces() const {
    return allSpaces;
}
const vector<shared_ptr<Zone>>& World::getZones()const {
    return zones;
}

void World::setBossFinalName(const string& n) {
    bossFinalName = n;
}
void World::setPlayer(shared_ptr<Character> c) {
    player = c;
}
void World::advanceTurn() {
    currentTurn++;
}

void World::setComplete(bool won) {
    adventureComplete = true;
    playerWon = won;
}

void World::addZone(shared_ptr<Zone> zone) {
    zones.push_back(zone);
    auto spaces = zone->getAllSpaces();
    for (int i = 0; i < spaces.size(); i++) {
        Space* sp = spaces[i];
        allSpaces.push_back(sp);
    }
}

void World::addEnemy(shared_ptr<Enemy> e) {
    enemies.push_back(e);
}

void World::addObjective(shared_ptr<Objective> obj) {
    mainQuest->addChild(obj);
    if (player) {
        player->addObjective(obj);
    }
}

Space* World::findSpace(const string& id) const {
    for (int i = 0; i < allSpaces.size(); i++) {
        Space* sp = allSpaces[i];
        if (sp->getId() == id) return sp;
    }
    return nullptr;
}

shared_ptr<Enemy> World::findEnemy(const string& name) const {
    for (int i = 0; i < enemies.size(); i++) {
        if (enemies[i]->getName() == name) {
            return enemies[i];
        }
    }
    return nullptr;
}

void World::setStartingSpace(const string& spaceId) {
    currentSpace = findSpace(spaceId);
    if (!currentSpace) {
        throw runtime_error("Espacio inicial no encontrado: " + spaceId);
    }
}

bool World::movePlayer(const string& direction) {
    if (!currentSpace) {
        return false;
    }
    Connection* conn = currentSpace->getConnection(direction);
    if (!conn) {
        return false;
    }
    if (conn->isLocked()) {
        string keyName = conn->getKey();
        shared_ptr<Item> key = player->getInventory().find(keyName);
        if (key) {
            conn->unlock();
            cout << "Usaste '" << keyName << "' para desbloquear el pasaje!\n";
        } else {
            cout << "Bloqueado! Necesitas: " << keyName << "\n";
            return false;
        }
    }
    currentSpace = conn->getDestination();
    currentSpace->markVisited();
    return true;
}

void World::checkObjectives() {
    for (auto& child : mainQuest->getChildren()) {

        //Goal:defeat the boss
        if (child->getId() == "defeat_boss") {
            shared_ptr<Enemy> boss = findEnemy(bossFinalName);
            if (boss && !boss->isAlive() && child->isPending()) {
                child->complete();
            }
        }

        //Goal:explore the world (visit at least 6 part)
        if (child->getId() == "explore") {
            int visited = 0;
        for (int i = 0; i < (int)allSpaces.size(); i++) {
            if (allSpaces[i]->isVisited()) visited++;
        }
            if (visited >= 6 && child->isPending())
                child->complete();
        }

        //Goal: survive
        if (child->getId() == "survive") {
            if (playerWon && child->isPending())
                child->complete();
        }
    }
    mainQuest->checkChildren();
}

nlohmann::json World::toJson() const {
    return {{"name",worldName},{"theme",theme},{"turn",currentTurn},{"won",playerWon}};
}

void World::fromJson(const nlohmann::json&) {

}