//
// Created by carba on 31/5/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ISERIALIZABLE_H
#define CARLOSBADILLAARIAS_PROYECTO2_ISERIALIZABLE_H
#include "json.hpp"
using namespace std;

//This interface can be used by any class that needs to load or save to JSON
class ISerializable {
public:
    virtual nlohmann::json toJson() const = 0;
    virtual void fromJson(const nlohmann::json &json) = 0;
    virtual ~ISerializable() = default;
};



#endif //CARLOSBADILLAARIAS_PROYECTO2_ISERIALIZABLE_H
