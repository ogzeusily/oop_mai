cmake_minimum_required(VERSION 3.16)

project(OOP207_MAI_Autumn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)

add_executable(main_app main.cpp src/separator.cpp)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)

FetchContent_MakeAvailable(googletest)

add_executable(run_tests tests/test.cpp src/separator.cpp)

target_link_libraries(run_tests GTest::gtest GTest::gtest_main pthread)

enable_testing()
add_test(NAME SeparatorTests COMMAND run_tests)