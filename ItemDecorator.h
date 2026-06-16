//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ITEMDECORATOR_H
#define CARLOSBADILLAARIAS_PROYECTO2_ITEMDECORATOR_H
#include "Item.h"
#include <memory>
#include <string>
using namespace std;

class ItemDecorator : public Item {
protected:
    shared_ptr<Item> wrapped;

public:
    explicit ItemDecorator(shared_ptr<Item> item);
    string getCategory() const override;
    string getType() const override;
    void use() override;
    string describe() const override;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j)override;
};


class PoisonedItemDecorator : public ItemDecorator {
private:
    int poisonDamage;
public:
    PoisonedItemDecorator(shared_ptr<Item> item, int poisonDamage);
    int getPoisonDamage() const;
    string getType()const override;
    string describe()const override;
};
#endif //CARLOSBADILLAARIAS_PROYECTO2_ITEMDECORATOR_H
