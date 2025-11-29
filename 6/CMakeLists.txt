cmake_minimum_required(VERSION 3.10)
project(DungeonEditor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main executable
add_executable(main
    main.cpp
    src/point.cpp
    src/npc.cpp
    src/visitor.cpp
    src/observer.cpp
    src/factory.cpp
    src/dungeon.cpp
)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Test executable
enable_testing()

# Google Test setup
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(lab_tests
    tests/test.cpp
    src/point.cpp
    src/npc.cpp
    src/visitor.cpp
    src/observer.cpp
    src/factory.cpp
    src/dungeon.cpp
)

target_include_directories(lab_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(lab_tests PRIVATE gtest gtest_main)

add_test(NAME DungeonTests COMMAND lab_tests)
