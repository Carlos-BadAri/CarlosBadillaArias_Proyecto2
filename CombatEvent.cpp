//
// Created by carba on 10/6/2026.
//

#include "CombatEvent.h"
#include <iostream>
#include <vector>

using namespace std;

CombatEvent::CombatEvent(shared_ptr<Enemy> enemy, shared_ptr<Character> character)
    : GameEvent("combat_" + enemy->getName()),enemy(enemy), character(character),rounds(0), playerVictory(false) {
}

bool CombatEvent::getPlayerVictory() const {
    return playerVictory;
}

void CombatEvent::logLine(const string& msg, IObserver* logger) {
    if (logger) {
        logger->onEvent(msg);
    }
    cout << msg << "\n";
}

int CombatEvent::playerTurn() {
    cout << "\nTu turno:\n";
    cout << " 1-Atacar\n";
    cout << " 2-Usar objeto\n";
    cout << " 3-Huir\n";
    cout << "Opcion: ";
    string input;
    getline(cin, input);
    if (input == "2") {
        return 2;
    }
    if (input == "3") {
        return 3;
    }
    return 1;
}

bool CombatEvent::activate(IObserver* logger) {
    if (executed) {
        return false;
    }
    executed = true;

    logLine("Combate: " + character->getName() + " vs " + enemy->getName(), logger);
    if (enemy->getIsBoss()) {
        logLine("*** BATALLA CONTRA EL JEFE FINAL ***", logger);
    }
    if (enemy->isDecorated()) {
        logLine("(Este enemigo tiene poderes especiales!)", logger);
    }

    while (character->isAlive() && enemy->isAlive()) {
        rounds++;
        logLine("--- Ronda " + to_string(rounds) + " ---", logger);
        logLine(character->describe(), logger);
        logLine(enemy->describe(), logger);

        int action = playerTurn();

       auto playerAttack = [&]() {
            int dmg = character->getEffectiveAttack() + (rand() % 5);
            enemy->takeDamage(dmg);
            logLine(character->getName() + " ataca por " + to_string(dmg) + " de dannio!", logger);
        };

        if (action == 1) {
            playerAttack();
            if (!enemy->isAlive()) {
                break;
            }

        } else if (action == 2) {
            //You can only see the items, the weapons and the keys can't be used in the battle
            vector<shared_ptr<Item>> consumables;
            for (int i = 0; i < character->getInventory().getSize(); i++) {
                shared_ptr<Item> it = character->getInventory()[i];
                if (it->getCategory() == "consumable") {
                    consumables.push_back(it);
                }
            }
            if (consumables.empty()) {
                logLine("No tienes objetos utilizables en combate! Forzado a atacar.", logger);
                playerAttack();
                if (!enemy->isAlive()) {
                    break;
                }
            } else {
                cout << "\nObjetos:\n";
                for (size_t i = 0; i < consumables.size(); i++) {
                    cout << "  " << (i + 1) << ". " << consumables[i]->describe() << "\n";
                }
                cout << "  0. Salir y atacar\n";
                cout << "Nombre del objeto (o 0 para Salir y atacar): ";
                string itemName;
                getline(cin, itemName);

                if (itemName == "0") {
                    logLine(character->getName() + " sale del inventario y ataca!", logger);
                    playerAttack();
                    if (!enemy->isAlive()) {
                        break;
                    }
                } else if (character->useConsumable(itemName)) {
                    logLine("Usaste: " + itemName, logger);
                } else {
                    logLine("No se pudo usar ese objeto.", logger);
                }
            }

        } else if (action == 3) {
            if (rand() % 10 < 4) {
                logLine(character->getName() + " huyo del combate!", logger);
                playerVictory = false;
                return true;
            }
            logLine("No lograste huir!", logger);
        }

        if (enemy->isAlive()) {
            int enemyDmg = enemy->computeAttack() + (rand() % 4);
            character->takeDamage(enemyDmg);
            logLine(enemy->getName() + " ataca por " + to_string(enemyDmg) + " de dannio!", logger);
        }

        enemy->update();
    }

    if (character->isAlive()) {
        playerVictory = true;
        logLine(character->getName() + " derroto a " + enemy->getName(), logger);
        character->addExperience(enemy->getExperienceReward());
        character->addGold(rand() % 30 + 10);
        logLine("EXP ganada: " + to_string(enemy->getExperienceReward()), logger);
        for (auto& reward : enemy->getRewards()) {
            try {
                character->pickUpItem(reward);
                logLine("Obtuviste: " + reward->getName(), logger);
            } catch (const exception& e) {
                logLine("No se pudo recoger la recompensa: " + string(e.what()), logger);
            }
        }
    } else {
        playerVictory = false;
        logLine(character->getName() + " fuiste derrotado!", logger);
    }
    return playerVictory;
}

string CombatEvent::getSummary() const {
    return "Combate vs " + enemy->getName() + " | Rondas:" + to_string(rounds) + " | " + (playerVictory ? "VICTORIA" : "DERROTA");
}
void CombatEvent::onEvent(const string& m) {
    logLine(m,nullptr);
}