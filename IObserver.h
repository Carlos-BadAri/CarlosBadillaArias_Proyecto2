//
// Created by carba on 31/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_IOBSERVER_H
#define CARLOSBADILLAARIAS_PROYECTO2_IOBSERVER_H
#include <string>
using namespace std;

class IObserver {
public:
    virtual void onEvent(const string& m) = 0;
    virtual ~IObserver() = default;
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_IOBSERVER_H
