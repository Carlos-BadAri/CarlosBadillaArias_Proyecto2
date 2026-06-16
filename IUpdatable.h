//
// Created by carba on 31/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_IUPDATABLE_H
#define CARLOSBADILLAARIAS_PROYECTO2_IUPDATABLE_H

class IUpdatable {
    public:
    virtual void update() = 0;
    virtual ~IUpdatable() = default;};

#endif //CARLOSBADILLAARIAS_PROYECTO2_IUPDATABLE_H