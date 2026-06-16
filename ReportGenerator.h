//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_REPORTEGENERATOR_H
#define CARLOSBADILLAARIAS_PROYECTO2_REPORTEGENERATOR_H
#include <string>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "World.h"
#include "Logger.h"
using namespace std;

class ReportGenerator {
private:
    string outputPath;
    World* world;

    string timestamp() const;
    string bar(int len = 42) const;

public:
    ReportGenerator(const string& outputPath, World* world);
    void generate();
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_REPORTEGENERATOR_H
