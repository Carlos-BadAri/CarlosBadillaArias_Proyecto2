//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_SPACE_H
#define CARLOSBADILLAARIAS_PROYECTO2_SPACE_H

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Item.h"
#include "GameEvent.h"
#include "ISerializable.h"
using namespace std;

class Space;

class Connection {
private:
    string id;
    string direction;
    Space* destination;
    bool locked;
    string requiredKey;

public:
    Connection(const string& id, const string& direction, Space* destination, bool locked = false, const string& requiredKey="");
    string getId()const;
    string getDirection()const;
    Space* getDestination()const;
    bool isLocked()const;
    string getKey()const;
    void unlock();
};
class ISpaceComponent : public ISerializable {
public:
    virtual string getName()const = 0;
    virtual string getDescription()const = 0;
    virtual bool isZone()const = 0;
    virtual string getSummary()const = 0;
    virtual ~ISpaceComponent() = default;
};
class Space : public ISpaceComponent {
private:
    string id;
    string name;
    string description;
    string ambiance;
    bool visited;
    bool hasBossFlag;

    vector<shared_ptr<Item>> items;
    vector<shared_ptr<GameEvent>> events;
    vector<unique_ptr<Connection>> connections;

public:
    Space(const string& id, const string& name, const string& description,
        const string& ambiance = "",bool hasBoss = false);

    string getId() const;
    string getName()const override;
    string getDescription()const override;
    string getAmbiance()const;
    bool isVisited()const;
    bool hasBoss()const;
    bool isZone()const override;

    void markVisited();

    void addItem(shared_ptr<Item> item);
    void addEvent(shared_ptr<GameEvent> event);
    void addConnection(unique_ptr<Connection> conn);

    shared_ptr<Item> removeItem(const string& itemName);
    Connection* getConnection(const string& direction) const;

    const vector<shared_ptr<Item>>& getItems()const;
    const vector<shared_ptr<GameEvent>>& getEvents()const;
    const vector<unique_ptr<Connection>>& getConnections() const;

    bool hasItems() const;

    string getSummary() const override;
    string getFullDescription() const;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j) override;
};

class Zone : public ISpaceComponent {
private:
    string id;
    string name;
    string description;
    vector<shared_ptr<ISpaceComponent>> children;

public:
    Zone(const string& id, const string& name, const string& description);

    string getId() const;
    string getName() const override;
    string getDescription() const override;
    bool isZone() const override;
    void addChild(shared_ptr<ISpaceComponent> child);
    const vector<shared_ptr<ISpaceComponent>>& getChildren() const;
    vector<Space*> getAllSpaces() const;
    string getSummary() const override;
    nlohmann::json toJson()  const override;
    void fromJson(const nlohmann::json& j) override;
};


#endif //CARLOSBADILLAARIAS_PROYECTO2_SPACE_H
