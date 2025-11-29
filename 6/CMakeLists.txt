cmake_minimum_required(VERSION 3.10)
project(DungeonEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

set(SOURCES

    inc/point.h
    inc/npc.h
    inc/dungeon.h
    inc/battle.h
    inc/observer.h
    src/point.cpp
    src/npc.cpp
    src/dungeon.cpp
    src/battle.cpp
    src/observer.cpp
    main.cpp
)

add_executable(dungeon_editor ${SOURCES})

# For test compilation
if(ENABLE_TESTING)
    enable_testing()
endif()
