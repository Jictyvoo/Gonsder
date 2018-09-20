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
        src/model/CharacterSkill.cpp
        src/model/CharacterSkill.h
        src/model/LiveThing.cpp
        src/model/LiveThing.h
        src/model/MainCharacter.cpp
        src/model/MainCharacter.h
        src/model/SaveGame.cpp
        src/model/SaveGame.h
        src/util/os_check_use.h
        src/util/padrao_nome.h
        "src/view/Gonsder.cpp"
        src/view/UserStories.hpp)
