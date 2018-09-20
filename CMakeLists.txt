cmake_minimum_required(VERSION 3.12)
project(Gonsder_em_C__)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src)

add_executable(Gonsder_em_C__
        src/dina_string.h
        src/os_check_use.h
        src/padrao_nome.h
        src/Gonsder_RPG.c
        )
