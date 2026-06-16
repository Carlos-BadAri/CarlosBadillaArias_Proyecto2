//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_SIMULATIONENGIENE_H
#define CARLOSBADILLAARIAS_PROYECTO2_SIMULATIONENGIENE_H
#include <string>
#include <vector>
#include <memory>
#include "World.h"
#include "CombatEvent.h"
#include "NarrativeEvent.h"
#include "Weapon.h"
#include "Logger.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class SimulationEngine {
private:
    World* world;
    string enemiesFile;
    vector<unique_ptr<GameEvent>> runEvents;

    void log(const string& msg);
    void checkAndRunCombat();
    void checkNarratives();
    void handleItems();
    string promptMovement();

public:
    SimulationEngine(World* world, const string& enemiesFile);

    void start();
    void run();
    void finish();
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_SIMULATIONENGIENE_H
