cmake_minimum_required(VERSION 3.16)
project(oop_lab_three LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)
enable_testing()

add_library(oop_lab_three_lib
    src/figure.cpp
    src/figure_array.cpp
    src/geometry.cpp
    src/pentagon.cpp
    src/rhombus.cpp
    src/trapezoid.cpp
)

target_include_directories(oop_lab_three_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(oop_lab_three_app src/main.cpp)
target_link_libraries(oop_lab_three_app PRIVATE oop_lab_three_lib)

include(FetchContent)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(oop_lab_three_tests
    tests/figure_tests.cpp
)
target_link_libraries(oop_lab_three_tests
    PRIVATE
        oop_lab_three_lib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(oop_lab_three_tests)
