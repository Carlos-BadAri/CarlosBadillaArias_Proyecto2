//
// Created by carba on 8/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_ITEM_H
#define CARLOSBADILLAARIAS_PROYECTO2_ITEM_H
#include <string>
#include "IInteractable.h"
#include "ISerializable.h"
using namespace std;

//This is an abstract class that will be used to create objects in the world
class Item : public ISerializable, public IInteractable {
    protected:
    string name;
    string description;
    float weight;
    int value;

public:
    Item (const string& name, const string& description, float weight, int value);
    virtual ~Item ()=default;
    string getName () const;
    string getDescription () const;
    float getWeight () const;
    int getValue () const;

    //This method retunr the category name
    virtual string getCategory()const=0;
    virtual string getType() const=0;
    virtual void use()=0;

    void interact() override;
    string describe()const override;
};
#endif //CARLOSBADILLAARIAS_PROYECTO2_ITEM_H
