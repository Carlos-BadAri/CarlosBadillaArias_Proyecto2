//
// Created by carba on 31/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ICOMBATSTRATEGY_H
#define CARLOSBADILLAARIAS_PROYECTO2_ICOMBATSTRATEGY_H

#include <string>
using namespace std;

class Enemy; //Here I make a forward declaration to avoid circular inclusion

class ICombatStrategy {
public:
    virtual int calculateAttack (const Enemy& enemy) const = 0;
    virtual string getName () const = 0;
    virtual ~ICombatStrategy () = default;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_ICOMBATSTRATEGY_H
