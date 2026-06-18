#include <iostream>
#include <string>
#include <stdexcept>
#include <filesystem>
#include "FileLoader.h"
#include "ReportGenerator.h"
#include "Logger.h"
#include "SimulationEngine.h"
#include "Character.h"
#include "World.h"

using namespace std;

string readLine(const string& prompt);
Race selectRace();
void showTutorial();

int main() {
    cout << "\n";
    cout << "\n======================================\n";
    cout << "    UnAventura Medieval"<<endl;
    cout << "\n======================================\n";

    try {
        filesystem::create_directories("output");
        filesystem::create_directories("data");

        Logger::getInstance().setLogPath("output/adventure_log.txt");
        Logger::getInstance().log("Programa iniciado.");

        cout << "Cuentanos sobre tu heroe antes de comenzar.\n\n";
        string heroName = readLine("Nombre de tu heroe: ");
        string bossName = readLine("Nombre del jefe final: ");
        Race race = selectRace();

        showTutorial();

        FileLoader loader("data");
        World* world = loader.loadWorld("world.json", bossName);

        auto player = make_shared<Character>(heroName, race);
        world->setPlayer(player);

        cout << "\n" << player->getFullStatus();
        cout << "\nPresiona ENTER para comenzar tu aventura...";
        string dummy;
        getline(cin, dummy);

        SimulationEngine engine(world, "data/enemies.json");
        engine.start();

        ReportGenerator report("output/adventure_report.txt", world);
        report.generate();
        cout << "Reporte guardado: output/adventure_report.txt\n\n";

        delete world;

    } catch (const exception& e) {
        cerr << "\n[ERROR FATAL] " << e.what() << "\n";
        return 1;
    }

    return 0;
}
void showTutorial() {
    cout << "\n" << string(46, '=') << "\n";
    cout << "COMO JUGAR\n";
    cout << string(46, '-') << "\n";
    cout << "-Usa los numeros para moverte entre lugares\n";
    cout << "-Escribe [i] para ver tu inventario\n";
    cout << "-Escribe [s] para ver el estado de tu heroe\n";
    cout << "-Recoge objetos para mejorar tu personaje\n";
    cout << "-Equipa armas fuera de combate para hacer mas danio en combate\n";
    cout << "-Usa pociones durante el combate para curarte o mejorar tu ataque\n";
    cout << "-Encuentra la 'Llave de Hierro' para entrar a la mazmorra\n";
    cout << "-Derrota al jefe final para ganar\n";
    cout << string(46, '=') << "\n";
    cout << "\nPresiona ENTER para continuar...";
    string dummy;
    getline(cin, dummy);
}

string readLine(const string& prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    while (val.empty()) {
        cout << "  (no puede estar vacio) " << prompt;
        getline(cin, val);
    }
    return val;
}
Race selectRace() {
    cout << "\n======================================\n";
    cout << "  Elige tu raza:\n\n";
    cout << "  1-Humano: Stats balanceados\n";
    cout << "  2-Elfo: Alta agilidad y magia.+2 ATK\n";
    cout << "  3-Enano: Alta fuerza y defensa.+20 HP, +3 DEF\n";
    cout << "  4-Mago: Maximo poder magico.+5 ATK\n";
    cout << "  5-Hada: Agilidad y suerte extremas.-10 HP\n";
    cout << "\n======================================\n";
    cout << "Opcion [1-5]: ";
    string input;
    getline(cin, input);
    if (input == "2")
        return Race::ELF;
    if (input == "3")
        return Race::DWARF;
    if (input == "4")
        return Race::MAGE;
    if (input == "5")
        return Race::FAIRY;
    return Race::HUMAN;
}