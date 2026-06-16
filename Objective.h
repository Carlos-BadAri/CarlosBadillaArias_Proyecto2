//
// Created by carba on 9/6/2026.
//

#ifndef CARLOSBADILLAARIAS_PROYECTO2_OBJECTIVE_H
#define CARLOSBADILLAARIAS_PROYECTO2_OBJECTIVE_H
#include <string>
#include <vector>
#include <memory>
#include "ISerializable.h"
using namespace std;

enum class ObjectiveState { PENDING, COMPLETED, FAILED };

class Objective : public ISerializable {
protected:
    string id;
    string description;
    ObjectiveState state;
    bool mandatory;

public:
    Objective(const string& id, const string& description, bool mandatory = true);
    virtual ~Objective() = default;

    string getId() const;
    string getDescription() const;
    ObjectiveState getState() const;
    bool isMandatory() const;
    bool isPending()const;
    bool isCompleted() const;

    virtual void complete();
    virtual void fail();

    string getStateLabel() const;
    virtual string getSummary() const;

    nlohmann::json toJson() const override;
    void fromJson(const nlohmann::json& j)override;
};

class CompositeObjective : public Objective {
private:
    vector<shared_ptr<Objective>> children;

public:
    CompositeObjective(const string& id, const string& description,bool mandatory = true);
    void addChild(shared_ptr<Objective> child);
    const vector<shared_ptr<Objective>>& getChildren() const;
    void checkChildren();
    string getSummary()const override;
};

#endif //CARLOSBADILLAARIAS_PROYECTO2_OBJECTIVE_H
