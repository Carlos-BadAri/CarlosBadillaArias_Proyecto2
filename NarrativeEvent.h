//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_NARRATIVEEVENT_H
#define CARLOSBADILLAARIAS_PROYECTO2_NARRATIVEEVENT_H

#include "GameEvent.h"
#include <vector>
#include <string>
using namespace std;

class NarrativeEvent : public GameEvent {
private:
    string storyText;
    vector<string> choices;
    vector<string> consequences;
    int chosenOption;

public:
    NarrativeEvent(const string& name, const string& storyText);
    void addChoice(const string& choice, const string& consequence);
    bool activate(IObserver* logger) override;
    string getSummary() const override;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_NARRATIVEEVENT_H
