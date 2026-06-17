//
// Created by carba on 10/6/2026.
//

#include "SimulationEngine.h"
#include "Consumable.h"
#include <fstream>
#include <iostream>

using namespace std;

SimulationEngine::SimulationEngine(World* world, const string& enemiesFile) : world(world), enemiesFile(enemiesFile) {
}

void SimulationEngine::log(const string& msg) {
    Logger::getInstance().log(msg);
}

void SimulationEngine::checkAndRunCombat() {
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

    for (int i = 0; i < (int)sp->getEvents().size(); i++) {
        if (!sp->getEvents()[i]->wasExecuted()) {
            sp->getEvents()[i]->activate(&Logger::getInstance());
        }
    }

    // Ranma's market
    if (sp->getId() == "casa_bruja") {
        auto player = world->getPlayer();
        cout << "\nLa Bruja Ranma te mira fijamente.\n";
        cout << "  'Tengo una pocion de hongos danta. Restaura tu salud dependiendo de tu raza.'\n";
        cout << "  'Cuesta 60 de oro. Tienes " << player->getGold() << " de oro.'\n";
        cout << "Comprar? [1] Si   [2] No\n";
        cout << "Opcion: ";
        string input;
        getline(cin, input);

        if (input == "1") {
            if (player->getGold() >= 60) {
                player->addGold(-60);
                //Made the potion and give to the traveler
                auto pocion = make_shared<Consumable>(
                    "Pocion de Hongos Danta",
                    "Una pocion preparada por la Bruja Ranma. Restaura toda tu salud.",
                    0.5f, 30, 100, "heal", 1);
                try {
                    player->pickUpItem(pocion);
                    cout << "Compraste: Pocion de Hongos Danta.\n";
                    cout << "Te quedan " << player->getGold() << " de oro.\n";
                    log(player->getName() + " compro: Pocion de Hongos Danta");
                } catch (const exception& e) {
                    player->addGold(30); //return your gold if don't are space in your backpack
                    cout << "[!] No hay espacio en el inventario. Se te devolvio el oro.\n";
                }
            } else {
                cout << "No tienes suficiente oro.\n";
                cout << "  'Vuelve cuando tengas 30 de oro,' dice la bruja.\n";
            }
        } else {
            cout << "La bruja asiente y sigue revolviendo su caldero.\n";
        }
    }
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

        //ask if they want to equip the weapon
        if (found->getCategory() == "weapon") {
            cout << "Quieres equipar '"
                 << found->getName() << "'? [1] Si   [2] No\n";
            cout << "Opcion: ";
            string opcion;
            getline(cin, opcion);
            if (opcion == "1") {
                world->getPlayer()->equipWeapon(found->getName());
                cout << "Equipaste: " << found->getName() << "\n";
                log(world->getPlayer()->getName()
                    + " equipo: " + found->getName());
            }
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