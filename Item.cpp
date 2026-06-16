//
// Created by carba on 8/6/2026.
//

#include "Item.h"

Item::Item(const string &name, const string &description, float weight, int value):name(name), description(description), weight(weight), value(value) {
}

string Item::getName() const {
    return name;
}

string Item::getDescription() const {
    return description;
}

float Item::getWeight() const {
    return weight;
}

int Item::getValue() const {
    return value;
}

void Item::interact() {
    use();
}

string Item::describe() const {
    return "["+getType()+"]"+name+":"+description;
}
