//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_KEYITEM_H
#define CARLOSBADILLAARIAS_PROYECTO2_KEYITEM_H
#include "Item.h"
#include <string>
using namespace std;

class KeyItem : public Item {
private:
    string unlocksId;

public:
    KeyItem(const string& name, const string& description, float weight, int value, const string& unlocksId);

    string getUnlocksId() const;
    string getCategory() const override;
    string getType() const override;
    void   use() override;
    string describe() const override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j)override;
};
#endif //CARLOSBADILLAARIAS_PROYECTO2_KEYITEM_H
