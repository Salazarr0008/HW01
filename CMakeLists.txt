cmake_minimum_required(VERSION 3.20)
project(hw1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

add_library(hw1_lib
    src/station.cpp
    src/grid.cpp
    src/analysis.cpp
    src/report.cpp
)
target_include_directories(hw1_lib PUBLIC include)

add_executable(hw1 src/main.cpp)
target_link_libraries(hw1 PRIVATE hw1_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(hw1_tests tests/test_hw1.cpp)
target_link_libraries(hw1_tests PRIVATE hw1_lib GTest::gtest_main)
gtest_discover_tests(hw1_tests)
