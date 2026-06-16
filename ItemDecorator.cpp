//
// Created by carba on 9/6/2026.
//
#include "ItemDecorator.h"
using namespace std;

//ItemDecorator
ItemDecorator::ItemDecorator(shared_ptr<Item> item) : Item(item->getName(), item->getDescription(),item->getWeight(), item->getValue()),wrapped(item) {

}

string ItemDecorator::getCategory() const {
    return wrapped->getCategory();
}
string ItemDecorator::getType()const {
    return wrapped->getType();
}
void ItemDecorator::use() {
    wrapped->use();
}
string ItemDecorator::describe()const {
    return wrapped->describe();
}

nlohmann::json ItemDecorator::toJson()const {
    return wrapped->toJson();
}

void ItemDecorator::fromJson(const nlohmann::json& j) {
    wrapped->fromJson(j);
}

//PoisonedItemDecorator

PoisonedItemDecorator::PoisonedItemDecorator(shared_ptr<Item> item,int poisonDamage): ItemDecorator(item), poisonDamage(poisonDamage) {

}

int PoisonedItemDecorator::getPoisonDamage() const {
    return poisonDamage;
}

string PoisonedItemDecorator::getType() const {
    return wrapped->getType() + "(Poisoned)";
}

string PoisonedItemDecorator::describe() const {
    return wrapped->describe() + " [Poison +" + to_string(poisonDamage) + "/turn]";
}