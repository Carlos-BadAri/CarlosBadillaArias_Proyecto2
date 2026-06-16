//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_COMBATEVENT_H
#define CARLOSBADILLAARIAS_PROYECTO2_COMBATEVENT_H

#include "GameEvent.h"
#include "Enemy.h"
#include "Character.h"
#include <memory>
#include <string>
using namespace std;

class CombatEvent : public GameEvent {
private:
    shared_ptr<Enemy> enemy;
    shared_ptr<Character> character;
    int rounds;
    bool playerVictory;

    void logLine(const string& msg, IObserver* logger);
    int playerTurn();

public:
    CombatEvent(shared_ptr<Enemy> enemy, shared_ptr<Character> character);
    bool getPlayerVictory() const;
    bool activate(IObserver* logger) override;
    string getSummary() const override;
    void onEvent(const string& m) override;
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_COMBATEVENT_H
