//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_INVENTORY_H
#define CARLOSBADILLAARIAS_PROYECTO2_INVENTORY_H

#include <string>
#include <stdexcept>
#include <memory>
#include "List.h"
#include "Item.h"
using namespace std;

class Inventory {
private:
    List<shared_ptr<Item>> items;
    int maxCapacity;
    float maxWeight;
    float currentWeight;

public:
    Inventory(int maxCapacity = 10, float maxWeight = 50.0f) : maxCapacity(maxCapacity), maxWeight(maxWeight),currentWeight(0.0f) {

    }

    void add(shared_ptr<Item> item) {
        if (items.getSize() >= maxCapacity) {
            throw runtime_error("El inventario esta lleno! No puedes cargar mas objetos.");
        }
        if (currentWeight + item->getWeight() > maxWeight) {
            throw runtime_error("Demasiado pesado! No puedes agregar " + item->getName());
        }
        items.add(item);
        currentWeight += item->getWeight();
    }

    shared_ptr<Item> remove(const string& itemName) {
        for (int i = 0; i < items.getSize(); i++) {
            if (items.get(i)->getName() == itemName) {
                shared_ptr<Item> found = items.get(i);
                items.removeAt(i);
                currentWeight -= found->getWeight();
                return found;
            }
        }
        throw runtime_error("Objeto '" + itemName + "' no encontrado en el inventario.");
    }

    shared_ptr<Item> find(const string& itemName) const {
        for (int i = 0; i < items.getSize(); i++) {
            if (items.get(i)->getName() == itemName) {
                return items.get(i);
            }
        }
        return nullptr;
    }

    bool isEmpty() const {
        return items.isEmpty();
    }
    int getSize() const {
        return items.getSize();
    }
    int getMaxCapacity()const {
        return maxCapacity;
    }
    float getCurrentWeight() const {
        return currentWeight;
    }

    shared_ptr<Item> operator[](int index) const {
        return items.get(index);
    }

    string listContents() const {
        if (items.isEmpty()) {
            return "  (empty)\n";
        }
        string result;
        for (int i = 0; i < items.getSize(); i++) {
            result += "  " + to_string(i + 1) + ". "
                    + items.get(i)->describe() + "\n";
        }
        return result;
    }

    auto begin() {
        return items.begin();
    }
    auto end(){
        return items.end();
    }
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_INVENTORY_H
