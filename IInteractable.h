//
// Created by carba on 31/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_IITERACTABLE_H
#define CARLOSBADILLAARIAS_PROYECTO2_IITERACTABLE_H

#include <string>
using namespace std;

class IInteractable {
    public:
    virtual void interact()=0;
    virtual string describe() const = 0;
    virtual ~IInteractable() = default;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_IITERACTABLE_H
