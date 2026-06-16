//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_FILELOADER_H
#define CARLOSBADILLAARIAS_PROYECTO2_FILELOADER_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <map>
#include "World.h"
#include "GameFactories.h"
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class FileLoader {
private:
    string basePath;
    MedievalItemFactory itemFactory;
    MedievalEnemyFactory enemyFactory;

    json loadOrCreate(const string& filename,const json& defaultContent) const;
    json defaultWorld() const;
    json defaultSpaces() const;
    json defaultConnections() const;
    json defaultItems()const;
    json defaultEnemies(const string& bossName) const;
    json defaultObjectives() const;

public:
    explicit FileLoader(const string& basePath);
    World* loadWorld(const string& worldFile,const string& bossName) const;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_FILELOADER_H
