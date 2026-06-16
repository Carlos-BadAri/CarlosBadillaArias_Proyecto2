//
// Created by carba on 10/6/2026.
//
#include "FileLoader.h"
using namespace std;

FileLoader::FileLoader(const string& basePath) : basePath(basePath) {
}

json FileLoader::loadOrCreate(const string& filename, const json& defaultContent) const {
    string fullPath = basePath + "/" + filename;
    ifstream fin(fullPath);
    if (!fin.is_open()) {
        cout << "[FileLoader] '" << filename << "' no encontrado. Creando con valores por defecto.\n";
        ofstream fout(fullPath);
        if (!fout.is_open()) {
            throw runtime_error("No se pudo crear el archivo: " + fullPath);
        }
        fout << defaultContent.dump(2);
        fout.close();
        return defaultContent;
    }
    json data;
    try {
        fin >> data;
    } catch (const json::parse_error& e) {
        throw runtime_error("Error de JSON en " + fullPath + ": " + string(e.what()));
    }
    return data;
}

json FileLoader::defaultWorld() const {
    return {{"name","El Reino de Eldenmoor"},{"theme","Fantasia Medieval"},
        {"start_space", "village_square"},{"items_file", "items.json"},{"spaces_file","spaces.json"},
        {"connections_file","connections.json"},{"enemies_file","enemies.json"},
        {"objectives_file","objectives.json"}};
}

json FileLoader::defaultSpaces() const {
    return {{"zones", {
        {{"id","zone_village"},{"name","La Aldea"},
         {"description","Zona de inicio"},
         {"spaces",{
            {{"id","village_square"},{"name","Plaza de la Aldea"},
             {"description","El corazon de Thornhaven."},
             {"ambiance","El humo se eleva de las casas en ruinas."},{"has_boss",false}},
            {{"id","blacksmith"},{"name","Forja del Herrero"},
             {"description","Un enano martilla una espada doblada."},
             {"ambiance","Olor a hierro fundido."},{"has_boss",false}}
         }}},
        {{"id","zone_wilds"},{"name","Las Tierras Salvajes"},
         {"description","Tierras peligrosas fuera de la aldea"},
         {"spaces",{
            {{"id","ancient_forest"},{"name","Bosque Ancestral"},
             {"description","Robles gigantes bloquean el cielo."},
             {"ambiance","Aullidos lejanos resuenan."},{"has_boss",false}},
            {{"id","ruined_chapel"},{"name","Capilla en Ruinas"},
             {"description","Una capilla profanada."},
             {"ambiance","Un canto tenue surge desde abajo."},{"has_boss",false}},
            {{"id","river_crossing"},{"name","Cruce del Rio"},
             {"description","Un puente de piedra sobre el rio."},
             {"ambiance","Niebla fria se eleva del agua."},{"has_boss",false}},
            {{"id","goblin_camp"},{"name","Campamento de Guerra Goblin"},
             {"description","Un campamento goblin caotico."},
             {"ambiance","Los goblins cacorean en la oscuridad."},{"has_boss",false}},
            {{"id","mountain_pass"},{"name","Paso de Montanna"},
             {"description","Un sendero estrecho en la montanna."},
             {"ambiance","El hielo cubre la piedra."},{"has_boss",false}},
            {{"id","wizard_tower"},{"name","Torre del Mago"},
             {"description","Una torre en ruinas con runas brillantes."},
             {"ambiance","La energia arcana crepita."},{"has_boss",false}}
         }}},
        {{"id","zone_dungeon"},{"name","La Mazmorra"},
         {"description","El oscuro corazon del mal"},
         {"spaces",{
            {{"id","dungeon_entrance"},{"name","Entrada de la Mazmorra"},
             {"description","Una enorme puerta de hierro."},
             {"ambiance","Huesos cubren los escalones."},{"has_boss",false}},
            {{"id","dungeon_depths"},{"name","Profundidades de la Mazmorra"},
             {"description","Pasajes subterraneos profundos."},
             {"ambiance","Las antorchas arden con llama azul."},{"has_boss",false}},
            {{"id","throne_room"},{"name","Trono de la Oscuridad"},
             {"description","Una vasta camara oscura."},
             {"ambiance","Rayos oscuros cruzan el techo."},{"has_boss",true}}
         }}}
    }}};
}

json FileLoader::defaultConnections() const {
    return {{"connections",{
        {{"id","c01"},{"from","village_square"},{"to","blacksmith"},      {"direction","norte"}, {"locked",false}},
        {{"id","c02"},{"from","village_square"},{"to","ancient_forest"},  {"direction","este"},  {"locked",false}},
        {{"id","c03"},{"from","blacksmith"},    {"to","village_square"},  {"direction","sur"},   {"locked",false}},
        {{"id","c04"},{"from","ancient_forest"},{"to","village_square"},  {"direction","oeste"}, {"locked",false}},
        {{"id","c05"},{"from","ancient_forest"},{"to","ruined_chapel"},   {"direction","norte"}, {"locked",false}},
        {{"id","c06"},{"from","ancient_forest"},{"to","river_crossing"},  {"direction","este"},  {"locked",false}},
        {{"id","c07"},{"from","ruined_chapel"}, {"to","ancient_forest"},  {"direction","sur"},   {"locked",false}},
        {{"id","c08"},{"from","ruined_chapel"}, {"to","wizard_tower"},    {"direction","este"},  {"locked",false}},
        {{"id","c09"},{"from","river_crossing"},{"to","ancient_forest"},  {"direction","oeste"}, {"locked",false}},
        {{"id","c10"},{"from","river_crossing"},{"to","goblin_camp"},     {"direction","norte"}, {"locked",false}},
        {{"id","c11"},{"from","river_crossing"},{"to","mountain_pass"},   {"direction","este"},  {"locked",false}},
        {{"id","c12"},{"from","goblin_camp"},   {"to","river_crossing"},  {"direction","sur"},   {"locked",false}},
        {{"id","c13"},{"from","mountain_pass"}, {"to","river_crossing"},  {"direction","oeste"}, {"locked",false}},
        {{"id","c14"},{"from","mountain_pass"}, {"to","dungeon_entrance"},{"direction","este"},  {"locked",false}},
        {{"id","c15"},{"from","wizard_tower"},  {"to","ruined_chapel"},   {"direction","oeste"}, {"locked",false}},
        {{"id","c16"},{"from","dungeon_entrance"},{"to","mountain_pass"}, {"direction","oeste"}, {"locked",false}},
        {{"id","c17"},{"from","dungeon_entrance"},{"to","dungeon_depths"},{"direction","abajo"}, {"locked",true},{"required_key","Llave de Hierro"}},
        {{"id","c18"},{"from","dungeon_depths"},{"to","dungeon_entrance"},{"direction","arriba"},{"locked",false}},
        {{"id","c19"},{"from","dungeon_depths"},{"to","throne_room"},     {"direction","norte"}, {"locked",true},{"required_key","Medallon Oscuro"}},
        {{"id","c20"},{"from","throne_room"},   {"to","dungeon_depths"},  {"direction","sur"},   {"locked",false}}
    }}};
}

json FileLoader::defaultItems() const {
    return {{"items",{
        {{"name","Espada Oxidada"},{"type","weapon"},
         {"description","Una vieja espada desgastada."},
         {"weight",3.5},{"value",10},{"damage",8},
         {"attack_type","slash"},{"durability",15},{"space_id","blacksmith"}},
        {{"name","Daga Elfica"},{"type","weapon"},
         {"description","Una delgada hoja elfica."},
         {"weight",1.2},{"value",45},{"damage",18},
         {"attack_type","pierce"},{"durability",25},
         {"space_id","ancient_forest"}},
        {{"name","Hacha de Guerra"},{"type","weapon"},
         {"description","Un brutal hacha de doble filo."},
         {"weight",6.0},{"value",60},{"damage",25},
         {"attack_type","blunt"},{"durability",30},{"space_id","goblin_camp"}},
        {{"name","Super Pocion"},{"type","consumable"},
         {"description","Restaura 80 HP"},
         {"weight",0.5},{"value",80},{"effect_amount",80},
         {"effect_type","heal"},{"uses",1},
         {"space_id","wizard_tower"}},
        {{"name","Pocion de Salud"},{"type","consumable"},
         {"description","Restaura 30 HP."},
         {"weight",0.5},{"value",20},
         {"effect_amount",30},{"effect_type","heal"},{"uses",1},
         {"space_id","village_square"}},
        {{"name","Pocion Mayor"},{"type","consumable"},
         {"description","Restaura 60 HP."},
         {"weight",0.5},{"value",50},
         {"effect_amount",60},{"effect_type","heal"},{"uses",1},
         {"space_id","ruined_chapel"}},
        {{"name","Brebaje Berserker"},{"type","consumable"},
         {"description","Aumenta el ATK en 8."},
         {"weight",0.5},{"value",35},
         {"effect_amount",8},{"effect_type","boost_attack"},{"uses",1},
         {"space_id","goblin_camp"}},
        {{"name","Llave de Hierro"},{"type","key"},
         {"description","Una llave pesada con extrannas runas."},
         {"weight",0.2},{"value",0},
         {"unlocks","c17"},{"space_id","mountain_pass"}},
        {{"name","Medallon Oscuro"},{"type","key"},
         {"description","Un medallon que pulsa con energia oscura."},
         {"weight",0.1},{"value",0},
         {"unlocks","c19"},{"space_id","dungeon_depths"}}
    }}};
}

json FileLoader::defaultEnemies(const string& bossName) const {
    return {{"enemies",{
        {{"name","Lobo del Bosque"},{"description","Un enorme lobo gris."},
         {"enemy_type","beast"},{"health",35},{"attack",9},{"defense",2},
         {"strategy","aggressive"},{"is_boss",false},{"experience",25},
         {"space_id","ancient_forest"}},
        {{"name","Espectro de la Capilla"},{"description","Un fantasma que drena vida."},
         {"enemy_type","undead"},{"health",45},{"attack",12},{"defense",1},
         {"strategy","random"},{"is_boss",false},{"experience",35},
         {"space_id","ruined_chapel"}},
        {{"name","Trol del Rio"},{"description","Un enorme trol."},
         {"enemy_type","troll"},{"health",70},{"attack",15},{"defense",5},
         {"strategy","aggressive"},{"is_boss",false},{"experience",50},
         {"space_id","river_crossing"},{"armored",true},{"armor_bonus",3}},
        {{"name","Jefe Guerrero Goblin"},{"description","Lider de los goblins."},
         {"enemy_type","goblin"},{"health",60},{"attack",13},{"defense",4},
         {"strategy","aggressive"},{"is_boss",false},{"experience",60},
         {"space_id","goblin_camp"}},
        {{"name","Golem de Montanna"},{"description","Una criatura de roca viva."},
         {"enemy_type","golem"},{"health",90},{"attack",18},{"defense",8},
         {"strategy","defensive"},{"is_boss",false},{"experience",70},
         {"space_id","mountain_pass"}},
        {{"name","Caballero de las Sombras"},{"description","Un guerrero de la oscuridad."},
         {"enemy_type","undead"},{"health",100},{"attack",20},{"defense",10},
         {"strategy","aggressive"},{"is_boss",false},{"experience",80},
         {"space_id","dungeon_depths"},{"enraged",true},{"rage_bonus",4}},
        {{"name",bossName},{"description","El mal supremo."},
         {"enemy_type","boss"},{"health",200},{"attack",30},{"defense",15},
         {"strategy","random"},{"is_boss",true},{"experience",500},
         {"space_id","throne_room"},{"enraged",true},{"rage_bonus",8}}
    }}};
}

json FileLoader::defaultObjectives() const {
    return {{"objectives",{
        {{"id","explorar"},{"description","Explorar el reino"},{"mandatory",false}},
        {{"id","derrotar_al_jefe"},{"description","Derrotar al jefe final"},{"mandatory",true}},
        {{"id","sobrevivir"},{"description","Sobrevivir la aventura"},{"mandatory",true}}
    }}};
}

World* FileLoader::loadWorld(const string& worldFile, const string& bossName) const {
    json worldData = loadOrCreate(worldFile, defaultWorld());

    World* world = new World(worldData.value("name","Unknown World"), worldData.value("theme", "Medieval"));
    world->setBossFinalName(bossName);

    json itemData = loadOrCreate(worldData.value("items_file", "items.json"), defaultItems());

    map<string, shared_ptr<Item>> itemMap;
    for (auto& d : itemData["items"]) {
        try {
            shared_ptr<Item> item = itemFactory.createItem(d);
            itemMap[item->getName()] = item;
        } catch (const exception& e) {
            cerr << "[FileLoader] Saltando item: " << e.what() << "\n";
        }
    }

    json spaceData = loadOrCreate(worldData.value("spaces_file", "spaces.json"), defaultSpaces());

    for (auto& zd : spaceData["zones"]) {
        auto zone = make_shared<Zone>(zd["id"], zd["name"], zd.value("description",""));
        for (auto& sd : zd["spaces"]) {
            auto space = make_shared<Space>(
                sd["id"], sd["name"],
                sd.value("description",""),
                sd.value("ambiance",""),
                sd.value("has_boss", false));
            zone->addChild(space);
        }
        world->addZone(zone);
    }

    for (auto& d : itemData["items"]) {
        if (!d.contains("space_id")) { continue; }
        Space* sp = world->findSpace(d["space_id"]);
        auto it = itemMap.find(d.value("name",""));
        if (sp && it != itemMap.end()) {
            sp->addItem(it->second);
        }
    }

    json connData = loadOrCreate(worldData.value("connections_file", "connections.json"), defaultConnections());

    for (auto& d : connData["connections"]) {
        Space* from = world->findSpace(d["from"]);
        Space* to = world->findSpace(d["to"]);
        if (!from || !to) {
            cerr << "[FileLoader] Conexion invalida: " << d["id"] << "\n";
            continue;
        }
        from->addConnection(make_unique<Connection>(
            d["id"], d["direction"], to,
            d.value("locked", false),
            d.value("required_key", "")));
    }

    json enemyData = loadOrCreate(worldData.value("enemies_file", "enemies.json"), defaultEnemies(bossName));

    for (auto& d : enemyData["enemies"]) {
        try {
            json ed = d;
            if (ed.value("is_boss", false)) { ed["name"] = bossName; }
            shared_ptr<Enemy> enemy = enemyFactory.createEnemy(ed);
            world->addEnemy(enemy);
        } catch (const exception& e) {
            cerr << "[FileLoader] Saltando enemigo: " << e.what() << "\n";
        }
    }

    json objData = loadOrCreate(worldData.value("objectives_file", "objectives.json"), defaultObjectives());

    for (auto& d : objData["objectives"]) {
        auto obj = make_shared<Objective>(d["id"], d["description"], d.value("mandatory", true));
        world->addObjective(obj);
    }

    string startId = worldData.value("start_space", "village_square");
    world->setStartingSpace(startId);

    return world;
}