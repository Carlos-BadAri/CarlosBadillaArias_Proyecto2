//
// Created by carba on 9/6/2026.
//

#include "Space.h"

using namespace std;

//Connection

Connection::Connection(const string& id, const string& direction,Space* destination, bool locked,const string& requiredKey)
    : id(id), direction(direction), destination(destination),locked(locked), requiredKey(requiredKey) {
}
string Connection::getId()const {
    return id;
}
string Connection::getDirection()const {
    return direction;
}
Space* Connection::getDestination() const {
    return destination;
}
bool Connection::isLocked()const {
    return locked;
}
string Connection::getKey()const {
    return requiredKey;
}

void Connection::unlock() {
    locked = false;
}

//Space

Space::Space(const string& id, const string& name,const string& description, const string& ambiance, bool hasBoss)
    : id(id), name(name), description(description),ambiance(ambiance), visited(false), hasBossFlag(hasBoss) {
}

string Space::getId()const {
    return id;
}
string Space::getName() const {
    return name;
}
string Space::getDescription()const {
    return description;
}
string Space::getAmbiance() const {
    return ambiance;
}
bool Space::isVisited() const {
    return visited;
}
bool Space::hasBoss()const {
    return hasBossFlag;
}
bool Space::isZone() const {
    return false;
}

void Space::markVisited() { visited = true; }

void Space::addItem(shared_ptr<Item> item) {
    items.push_back(item);
}
void Space::addEvent(shared_ptr<GameEvent> event) {
    events.push_back(event);
}

void Space::addConnection(unique_ptr<Connection> conn) {
    connections.push_back(move(conn));
}

shared_ptr<Item> Space::removeItem(const string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getName() == itemName) {
            shared_ptr<Item> found = *it;
            items.erase(it);
            return found;
        }
    }
    throw runtime_error("Objeto '" + itemName + "' no encontrado en " + name);
}

Connection* Space::getConnection(const string& direction) const {
    for (auto& c : connections) {
        if (c->getDirection() == direction) {
            return c.get();
        }
    }
    return nullptr;
}

const vector<shared_ptr<Item>>& Space::getItems() const {
    return items;
}
const vector<shared_ptr<GameEvent>>& Space::getEvents() const {
    return events;
}
const vector<unique_ptr<Connection>>& Space::getConnections() const {
    return connections;
}

bool Space::hasItems() const {
    return !items.empty();
}

string Space::getSummary() const {
    return name + (visited ? " [visitado]" : "");
}

string Space::getFullDescription() const {
    string s;
    s += "\n================================\n";
    s += "  " + name + "\n";
    s += "================================\n";
    s += description + "\n";
    if (!ambiance.empty()) {
        s += "[" + ambiance + "]\n";
    }

    if (!items.empty()) {
        s += "\nObjetos que hay aqui:\n";
        for (auto& i : items) s += " - " + i->describe() + "\n";
    }

    s += "\nSalidas:\n";
    if (connections.empty()) {
        s += "(no hay salidas)\n";
    } else {
        for (auto& c : connections) {
            string lock = c->isLocked() ? " [bloqueadp - necesitas: " + c->getKey() + "]" : "";
            s += "  - " + c->getDirection() + " -> " + c->getDestination()->getName() + lock + "\n";
        }
    }
    return s;
}

nlohmann::json Space::toJson() const {
    return {{"id",id},{"name", name},{"description",description},{"ambiance", ambiance},{"visited", visited},{"has_boss",hasBossFlag}};
}

void Space::fromJson(const nlohmann::json& j) {
    visited = j.value("visited", false);
}

//Zone

Zone::Zone(const string& id, const string& name, const string& description) : id(id), name(name), description(description) {
}

string Zone::getId()const {
    return id;
}
string Zone::getName()const {
    return name;
}
string Zone::getDescription() const {
    return description;
}
bool   Zone::isZone()const {
    return true;
}

void Zone::addChild(shared_ptr<ISpaceComponent> child) {
    children.push_back(child);
}

const vector<shared_ptr<ISpaceComponent>>& Zone::getChildren() const {
    return children;
}

vector<Space*> Zone::getAllSpaces() const{
    vector<Space*> result;
    for (size_t i = 0; i < children.size(); i++){
        if (children[i]->isZone() == false){
            result.push_back((Space*)children[i].get());
        }
        else{
            Zone* subZone = (Zone*)children[i].get();
            vector<Space*> subSpaces = subZone->getAllSpaces();
            for (size_t j = 0; j < subSpaces.size(); j++){
                result.push_back(subSpaces[j]);
            }
        }
    }

    return result;
}

string Zone::getSummary() const {
    string s = "Zona: " + name + "\n";
    for (auto& child : children)
        s += "  - " + child->getSummary() + "\n";
    return s;
}

nlohmann::json Zone::toJson() const {
    nlohmann::json j;
    j["id"]= id;
    j["name"]= name;
    j["description"]= description;
    j["is_zone"]= true;
    nlohmann::json arr = nlohmann::json::array();
    for (auto& c : children) arr.push_back(c->toJson());
    j["children"] = arr;
    return j;
}

void Zone::fromJson(const nlohmann::json&) {

}
