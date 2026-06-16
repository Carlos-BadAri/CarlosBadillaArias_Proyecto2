cmake_minimum_required(VERSION 4.2)
project(CarlosBadillaArias_Proyecto2)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.hpp
        DOWNLOAD_NO_EXTRACT TRUE
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include
)

FetchContent_MakeAvailable(nlohmann_json)
include_directories(include)


add_executable(CarlosBadillaArias_Proyecto2 main.cpp
        List.h
        Node.h
        include/json.hpp
        ISerializable.h
        IUpdatable.h
        IInteractable.h
        IObserver.h
        ICombatStrategy.h
        Item.cpp
        Item.h
        Entity.cpp
        Entity.h
        GameEvent.cpp
        GameEvent.h
        Weapon.cpp
        Weapon.h
        Consumable.cpp
        Consumable.h
        KeyItem.cpp
        KeyItem.h
        Inventory.h
        CombatStrategy.cpp
        CombatStrategy.h
        Enemy.cpp
        Enemy.h
        Objective.cpp
        Objective.h
        Character.cpp
        Character.h
        ItemDecorator.cpp
        ItemDecorator.h
        EnemyDecorator.cpp
        EnemyDecorator.h
        Space.cpp
        Space.h
        World.cpp
        World.h
        NarrativeEvent.cpp
        NarrativeEvent.h
        CombatEvent.cpp
        CombatEvent.h
        Logger.h
        ReportGenerator.cpp
        ReportGenerator.h
        GameFactories.cpp
        GameFactories.h
        FileLoader.cpp
        FileLoader.h
        SimulationEngine.cpp
        SimulationEngine.h)
