//
// Created by carba on 10/6/2026.
//

#include "ReportGenerator.h"

using namespace std;

ReportGenerator::ReportGenerator(const string& outputPath, World* world)
    : outputPath(outputPath), world(world) {
}

string ReportGenerator::timestamp() const {
    time_t t = time(nullptr);
    tm* info = localtime(&t);
    ostringstream oss;
    oss << put_time(info, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

string ReportGenerator::bar(int len) const {
    return string(len, '=');
}

void ReportGenerator::generate() {
    ofstream file(outputPath);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de reporte: " + outputPath);
    }
    auto player = world->getPlayer();
    file << bar() << "\n";
    file << " Reporte final de aventura\n";
    file << "  " << world->getWorldName() << "\n";
    file << "  Generado: " << timestamp() << "\n";
    file << bar() << "\n\n";
    file << "Mundo\n";
    file << "  Nombre: " << world->getWorldName() << "\n";
    file << "  Tema: " << world->getTheme() << "\n";
    file << "  Turnos: " << world->getCurrentTurn() << "\n\n";
    file << "Resultado\n";
    file << "  Desenlace: " << (world->getPlayerWon() ? "Victoria" : "Derrota") << "\n";
    file << "  Jefe final: " << world->getBossFinalName() << "\n\n";
    if (player) {
        file << "Personaje\n";
        file << player->getFullStatus() << "\n";
    }
    file << "Objetivps\n";
    file << world->getMainQuest()->getSummary() << "\n";
    file << "Zonas y Espacios Explorados\n";
    for (auto& zone : world->getZones()) {
        file << "  Zona: " << zone->getName() << "\n";
        for (int i = 0; i < zone->getAllSpaces().size(); i++) {
            Space* sp = zone->getAllSpaces()[i];
            file << "    [" << (sp->isVisited() ? "X" : " ") << "] " << sp->getName() << "\n";
        }
    }
    file << "\n";
    file << "Enemigos\n";
    for (int i = 0; i < world->getEnemies().size(); i++) {
        auto& e = world->getEnemies()[i];
        file << "  - " << e->getName() << (e->isAlive() ? " [vivo]" : " [derrotado]") << "\n";
    }
    file << "\n";
    file << "Resumen de bitacora\n";
    file << "  Total de eventos: " << Logger::getInstance().getEntryCount() << "\n";
    file << "  Archivo: output/adventure_log.txt\n\n";
    file << bar() << "\n  Fin del reporte\n" << bar() << "\n";
    file.close();
    Logger::getInstance().log("Reporte generado: " + outputPath);
}
