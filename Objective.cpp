//
// Created by carba on 9/6/2026.
//

#include "Objective.h"

using namespace std;

//Objective

Objective::Objective(const string& id, const string& description, bool mandatory) : id(id),
description(description), state(ObjectiveState::PENDING), mandatory(mandatory) {
}

string Objective::getId()const {
    return id;
}
string Objective::getDescription()const {
    return description;
}
ObjectiveState Objective::getState() const {
    return state;
}
bool Objective::isMandatory()const {
    return mandatory;
}
bool Objective::isPending() const {
    return state == ObjectiveState::PENDING;
}
bool Objective::isCompleted()const {
    return state == ObjectiveState::COMPLETED;
}

void Objective::complete() {
    state = ObjectiveState::COMPLETED;
}
void Objective::fail() {
    state = ObjectiveState::FAILED;
}

string Objective::getStateLabel() const {
    if (state == ObjectiveState::PENDING) {
        return "Pendiente";
    }
    if (state == ObjectiveState::COMPLETED) {
        return "Completado";
    }
    return "Fallado";
}

string Objective::getSummary() const {
    return "[" + getStateLabel() + "] " + description;
}

nlohmann::json Objective::toJson() const {
    return {{"id",id},{"description",description},{"state",getStateLabel()},{"mandatory",mandatory}
    };
}

void Objective::fromJson(const nlohmann::json& j) {
    string s = j.value("state","PENDING");
    if(s == "COMPLETED") state = ObjectiveState::COMPLETED;
    else if (s == "FAILED") state = ObjectiveState::FAILED;
    else state = ObjectiveState::PENDING;
}

//CompositeObjective
CompositeObjective::CompositeObjective(const string& id,const string& description,bool mandatory) : Objective(id, description, mandatory) {
}

void CompositeObjective::addChild(shared_ptr<Objective> child) {
    children.push_back(child);
}

const vector<shared_ptr<Objective>>& CompositeObjective::getChildren() const {
    return children;
}

void CompositeObjective::checkChildren() {
    bool anyFailed = false;
    bool allDone= true;
    for (auto& child : children) {
        if (child->isMandatory() && child->getState() == ObjectiveState::FAILED) {
            anyFailed = true;
        }
        if (child->isMandatory() && !child->isCompleted()) {
            allDone = false;
        }
    }
    if (anyFailed) {
        state = ObjectiveState::FAILED;
    }
    else if (allDone) {
        state = ObjectiveState::COMPLETED;
    }
}
string CompositeObjective::getSummary() const {
    string s = "[" + getStateLabel() + "] " + description + "\n";
    for (auto& child : children) {
        s += " - " + child->getSummary() + "\n";
    }
    return s;
}