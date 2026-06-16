//
// Created by carba on 10/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_LOGGER_H
#define CARLOSBADILLAARIAS_PROYECTO2_LOGGER_H
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "IObserver.h"
using namespace std;

//This is Singleton, since the instance is static and is in the .h file, with static it doesn't need the .cpp file
class Logger : public IObserver {
private:
    vector<string> entries;
    string logPath;

    Logger() : logPath("output/adventure_log.txt") {}

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    string timestamp() const {
        time_t t = time(nullptr);
        tm* info = localtime(&t);
        ostringstream oss;
        oss << put_time(info, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void setLogPath(const string& path) {
        logPath = path;
    }

    void log(const string& message) {
        entries.push_back("[" + timestamp() + "] " + message);
    }

    void onEvent(const string& message) override {
        log(message);
    }

    void save() const {
        ofstream file(logPath);
        if (!file.is_open())
            throw runtime_error("No se pudo abrir el archivo de bitacora: " + logPath);
        file << "========================================\n";
        file << "  Bitacora de aventura\n";
        file << "  Generada: " << timestamp() << "\n";
        file << "========================================\n\n";
        for (const string& e : entries)
            file << e << "\n";
        file << "\n========================================\n";
        file << "  Total de entradas: " << entries.size() << "\n";
        file << "========================================\n";
    }

    int getEntryCount() const {
        return (int)entries.size();
    }
    const vector<string>& getEntries()const {
        return entries;
    }
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_LOGGER_H
