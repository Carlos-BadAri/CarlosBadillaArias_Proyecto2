//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_GAMEEVENT_H
#define CARLOSBADILLAARIAS_PROYECTO2_GAMEEVENT_H
#include <string>
#include "IUpdatable.h"
#include "IObserver.h"
using namespace std;
//This is an abstract class that serves for all events that may occur

class GameEvent : public IUpdatable, public IObserver {
protected:
    string name;
    bool executed;
public:
    explicit GameEvent(const string& name);
    virtual ~GameEvent() = default;
    string getName() const;
    bool wasExecuted() const;

    virtual bool activate(IObserver* logger)=0;
    virtual string getSummary() const=0;
    void update() override;

};
#endif //CARLOSBADILLAARIAS_PROYECTO2_GAMEEVENT_H
