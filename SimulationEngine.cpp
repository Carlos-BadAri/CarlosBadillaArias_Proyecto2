//
// Created by carba on 10/6/2026.
//

#include "SimulationEngine.h"
#include <fstream>
#include <iostream>

using namespace std;

SimulationEngine::SimulationEngine(World* world, const string& enemiesFile) : world(world), enemiesFile(enemiesFile) {
}

void SimulationEngine::log(const string& msg) {
    Logger::getInstance().log(msg);
}

void SimulationEngine::checkAndRunCombat() {
    cout << "\nSientes una presencia extrannia en este lugar...\n";
    cout << "Presiona ENTER para continuar.";
    string pause;
    getline(cin, pause);

    Space* sp = world->getCurrentSpace();
    auto player = world->getPlayer();
    if (!sp || !player)
        return;

    ifstream f(enemiesFile);
    if (!f.is_open())
        return;

    json data;
    f >> data;

    for (auto& ed : data["enemies"]) {
        if (!ed.contains("space_id"))
            continue;
        if (ed["space_id"] != sp->getId())
            continue;

        string ename = ed.value("is_boss", false)? world->getBossFinalName() : ed.value("name", "");

        shared_ptr<Enemy> enemy = world->findEnemy(ename);
        if (!enemy || !enemy->isAlive())
            continue;

        cout << "\n Un " << enemy->getEnemyType() << " llamado '" << enemy->getName() << "' te bloquea el paso\n";
        log("Combate iniciado en: " + sp->getName() + " contra " + enemy->getName());

        auto combat = make_unique<CombatEvent>(enemy, player);
        combat->activate(&Logger::getInstance());
        bool won = combat->getPlayerVictory();
        log(combat->getSummary());
        runEvents.push_back(move(combat));

        if (!player->isAlive()) {
            world->setComplete(false);
            return;
        }
        if (won) {
            world->checkObjectives();
            if (enemy->getIsBoss()) {
                cout << "\nHas derrotado al jefe final!\n";
                world->setComplete(true);
            }
        }
    }
}

void SimulationEngine::checkNarratives() {
    Space* sp = world->getCurrentSpace();
    if (!sp) return;
    for (auto& ev : sp->getEvents())
        if (!ev->wasExecuted())
            ev->activate(&Logger::getInstance());
}

void SimulationEngine::handleItems() {
    Space* sp = world->getCurrentSpace();
    if (!sp->hasItems()) return;

    cout << "\nObjetos en este lugar:\n";
    const auto& items = sp->getItems();
    for (int i = 0; i < (int)items.size(); i++) {
        cout << "  [" << (i + 1) << "] "
             << items[i]->describe() << "\n";
    }
    cout << "Recoger? (elija el numero o ENTER para omitir): ";

    string input;
    getline(cin, input);
    if (input.empty()) return;

    try {
        int idx = stoi(input) - 1;
        if (idx < 0 || idx >= (int)items.size()) {
            cout << "Numero invalido.\n";
            return;
        }
        string itemName = items[idx]->getName();
        shared_ptr<Item> found = sp->removeItem(itemName);
        world->getPlayer()->pickUpItem(found);
        cout << "Recogiste: " << found->getName() << "\n";
        log(world->getPlayer()->getName()
            + " recogio: " + found->getName());

        if (found->getCategory() == "weapon"
            && !world->getPlayer()->getEquippedWeapon()) {
            world->getPlayer()->equipWeapon(found->getName());
            cout << "Equipaste: " << found->getName() << "\n";
            }
    } catch (const invalid_argument&) {
        cout << "Entrada invalida.\n";
    } catch (const exception& e) {
        cout << "[!] " << e.what() << "\n";
    }
}

string SimulationEngine::promptMovement() {
    Space* sp = world->getCurrentSpace();
    cout << "\nA donde vas?\n";

    vector<string> dirs;
    int i = 1;
    for (auto& c : sp->getConnections()) {
        string lock = c->isLocked() ? " [Bloqueado]" : "";
        cout << "  [" << i++ << "] " << c->getDirection() << " -> " << c->getDestination()->getName() << lock << "\n";
        dirs.push_back(c->getDirection());
    }
    cout << "[i] Inventario [s] Estado [e] Equipar arma\n";
    cout << "Opcion: ";

    string input;
    getline(cin, input);

    if (input == "i") {
        cout << "\n" << world->getPlayer()->getInventory().listContents();
        return "";
    }
    if (input == "s") {
        cout << "\n" << world->getPlayer()->getFullStatus();
        return "";
    }
    if (input == "e") {
        cout << "\nInventario:\n" << world->getPlayer()->getInventory().listContents();
        cout << "Nombre del arma a equipar: ";
        string weaponName;
        getline(cin, weaponName);
        if (world->getPlayer()->equipWeapon(weaponName)) {
            cout << "Equipaste: " << weaponName << "\n";
            log(world->getPlayer()->getName() + " equipo el arma: " + weaponName);
        } else {
            cout << "[!] No se encontro el arma '" << weaponName << "' en el inventario.\n";
        }
        return "";
    }
    try {
        int idx = stoi(input) - 1;
        if (idx >= 0 && idx < (int)dirs.size()) return dirs[idx];
    } catch (...) {}

    for (auto& d : dirs)
        if (d == input) return d;
    return "";
}

void SimulationEngine::start() {
    log("=== Simulacion Iniciada ===");
    log("Mundo: " + world->getWorldName());
    log("Jugador: " + world->getPlayer()->describe());

    cout << "\n" << string(46, '=') << "\n";
    cout << "  Bienvenido a: " << world->getWorldName() << "\n";
    cout << string(46, '=') << "\n";

    Space* start = world->getCurrentSpace();
    if (start) {
        start->markVisited();
        cout << start->getFullDescription();
    }
    run();
}

void SimulationEngine::run() {
    while (!world->isComplete()) {
        world->advanceTurn();
        log("--- Turno " + to_string(world->getCurrentTurn()) + " ---");

        Space* sp = world->getCurrentSpace();
        if (!sp)
            break;

        checkNarratives();
        checkAndRunCombat();
        if (world->isComplete())
            break;

        handleItems();

        cout << "\n" << string(46, '-') << "\n";
        cout << "Ubicacion : " << sp->getName() << "\n";
        cout << world->getPlayer()->describe() << "\n";
        cout << "\nObjetivos:\n";
        cout << world->getMainQuest()->getSummary();

        string dir = "";
        while (dir.empty()) dir = promptMovement();

        bool moved = world->movePlayer(dir);
        if (moved) {
            cout << world->getCurrentSpace()->getFullDescription();
            log("Se movio " + dir + " hacia: " + world->getCurrentSpace()->getName());
            world->checkObjectives();
        }

        if (!world->getPlayer()->isAlive()) {
            world->setComplete(false);
            break;
        }
    }
    finish();
}

void SimulationEngine::finish() {
    auto player = world->getPlayer();

    //count visited places and defeat enemies
    int visited = 0;
    for (Space* sp : world->getAllSpaces())
        if (sp->isVisited()) visited++;

    int derrotados = 0;
    for (auto& e : world->getEnemies())
        if (!e->isAlive()) derrotados++;

    cout << "\n" << string(46, '=') << "\n";
    if (world->getPlayerWon()) {
        cout <<"VICTORIA! Tu leyenda sera recordada!\n";
    } else {
        cout <<"DERROTA. Tu aventura termina aqui.\n";
    }
    cout << string(46, '-') << "\n";
    if (player) {
        cout <<"Heroe:" << player->getName()<< "\n";
        cout <<"Nivel alcanzado:"<< player->getLevel() << "\n";
        cout <<"Oro recolectado:"<< player->getGold() << "\n";
    }
    cout << "Turnos jugados:"<< world->getCurrentTurn() << "\n";
    cout << "Lugares visitados:"<< visited << "\n";
    cout << "Enemigos derrotados:"<< derrotados << "\n";
    cout << string(46, '=') << "\n";

    log("===FIN:"+string(world->getPlayerWon() ?"VICTORIA":"DERROTA")+"===");

    try {
        Logger::getInstance().save();
        cout << "\nBitacora guardada: output/adventure_log.txt\n";
    } catch (const exception& e){
        cerr << "Error al guardar bitacora: " << e.what() << "\n";
    }
}