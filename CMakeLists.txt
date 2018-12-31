cmake_minimum_required(VERSION 3.12)
project(Gonsder_em_C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)
include_directories(src/controller)
include_directories(src/model)
include_directories(src/util)
include_directories(src/view)

add_executable(Gonsder_em_C__
        src/controller/CombatController.cpp
        src/controller/CombatController.h
        src/controller/Director.cpp
        src/controller/Director.h
        src/model/Backpack.cpp
        src/model/Backpack.h
        src/model/Skills.cpp
        src/model/Skills.h
        src/model/LiveThing.cpp
        src/model/LiveThing.h
        src/model/entity/Player.cpp
        src/model/entity/Player.h
        src/model/business/SaveGame.cpp
        src/model/business/SaveGame.h
        src/util/UsableEnums.h
        src/util/os_check_use.h
        src/util/name_partner.h
        "src/view/Gonsder.cpp"
        src/view/StoryScript.hpp)
