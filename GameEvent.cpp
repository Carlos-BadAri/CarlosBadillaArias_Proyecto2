//
// Created by carba on 9/6/2026.
//

#include "GameEvent.h"
GameEvent::GameEvent(const string &name):name(name),executed(false) {
}

string GameEvent::getName() const {
    return name;
}

bool GameEvent::wasExecuted() const {
    return executed;
}

void GameEvent::update() {
}