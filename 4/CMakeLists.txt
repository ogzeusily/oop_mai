cmake_minimum_required(VERSION 3.10)
project(OOP_MAI_207)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(lab_lib INTERFACE)
target_include_directories(lab_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE lab_lib)


enable_testing()
add_executable(lab_tests tests/test.cpp)
target_link_libraries(lab_tests PRIVATE lab_lib gtest_main)
add_test(NAME lab_tests COMMAND lab_tests)