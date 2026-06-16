//
// Created by carba on 10/6/2026.
//

#include "NarrativeEvent.h"
#include <iostream>
using namespace std;

NarrativeEvent::NarrativeEvent(const string& name, const string& storyText)
    : GameEvent(name), storyText(storyText), chosenOption(-1) {
}

void NarrativeEvent::addChoice(const string& choice, const string& consequence) {
    choices.push_back(choice);
    consequences.push_back(consequence);
}

bool NarrativeEvent::activate(IObserver* logger) {
    if (executed) {
        return true;
    }
    executed = true;
    cout << "\n" << storyText << "\n";
    if (logger) { logger->onEvent("Narrativa: " + storyText.substr(0, 60)); }
    if (!choices.empty()) {
        cout << "\nQue decides hacer?\n";
        for (int i = 0; i < (int)choices.size(); i++) {
            cout << "  [" << (i + 1) << "] " << choices[i] << "\n";
        }
        cout << "Opcion: ";
        string input;
        getline(cin, input);
        try {
            chosenOption = stoi(input) - 1;
            if (chosenOption < 0 || chosenOption >= (int)choices.size()) {
                chosenOption = 0;
            }
        } catch (...) {
            chosenOption = 0;
        }
        cout << "\n> " << consequences[chosenOption] << "\n";
        if (logger) {
            logger->onEvent("Jugador eligio: " + choices[chosenOption]);
        }
    }
    return true;
}

string NarrativeEvent::getSummary() const {
    return "Narrativa["+name+"]"+(chosenOption >= 0 ? " | Eligio: "+choices[chosenOption] : "");
}
