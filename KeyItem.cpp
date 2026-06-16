//
// Created by carba on 9/6/2026.
//

#include "KeyItem.h"

using namespace std;

KeyItem::KeyItem(const string& name, const string& description,float weight, int value, const string& unlocksId)
    :Item(name, description, weight, value),unlocksId(unlocksId) {
}

string KeyItem::getUnlocksId() const {
    return unlocksId;
}

string KeyItem::getCategory() const {
    return "key";
}
string KeyItem::getType()const {
    return "Key";
}

void KeyItem::use() {
 //la logica de esto esta en Conection
}

string KeyItem::describe() const {
    return "[Key]"+ name+ "|unlocks:"+unlocksId;
}

nlohmann::json KeyItem::toJson() const {
    return {{"type","key"},{"name",name},{"description",description},{"weight",weight},
        {"value",value},{"unlocks",unlocksId}};
}

void KeyItem::fromJson(const nlohmann::json& j) {
    unlocksId =j.value("unlocks", "");
}