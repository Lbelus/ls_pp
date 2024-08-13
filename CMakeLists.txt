cmake_minimum_required(VERSION 3.22)
project(ls_pp VERSION 0.0.1 LANGUAGES CXX)

# GENERATE THE LIB OBJECT

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find NASM
enable_language(ASM_NASM)
if(NOT CMAKE_ASM_NASM_COMPILER_LOADED)
    message(FATAL_ERROR "NASM compiler not found")
endif()

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)


# Include extern submodule  cxxopts
add_subdirectory(extern/cxxopts)
target_include_directories(${TARGET_NAME} PUBLIC cxxopts)
target_link_libraries(${TARGET_NAME} PUBLIC cxxopts)

# Add source files excluding main.cpp
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
list(FILTER CPP_SOURCES EXCLUDE REGEX ".*main\\.cpp$")

# Create an object library from the source files
add_library(ls_ppObj OBJECT ${CPP_SOURCES})


if(ENABLE_CFLAGS)
    target_compile_options(ls_ppObj PRIVATE 
    $<$<COMPILE_LANGUAGE:C>:-fsanitize=address -Wall -Wextra -Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-fsanitize=address -Wall -Wextra -Werror>
    )
    # Link with sanitizer library for C and C++ targets
    target_link_libraries(ls_ppObj PRIVATE -fsanitize=address)
endif()



# Option to enable or disable GoogleTest
option(ENABLE_GTEST "Enable Google Test" OFF)

if(ENABLE_GTEST)
    enable_testing()
    find_package(GTest REQUIRED)

    # Add test executable
    add_executable(ls_pp_tests tests/ls_pp_tests.cc)
    target_link_libraries(th_rand_api_tests PRIVATE GTest::gtest_main ls_ppObj)

    include(GoogleTest)
    gtest_discover_tests(th_rand_api_tests)
endif()


# Create the main executable with main.cpp
add_executable(ls_pp src/main.cpp)
target_link_libraries(ls_pp PRIVATE ls_ppObj)
