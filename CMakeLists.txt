cmake_minimum_required(VERSION 3.8)
project(solucion)

set(CMAKE_CXX_STANDARD 11)

# Leemos todos los archivos fuentes en ./src
#file(GLOB SOURCE_FILES src/*.cpp src/*.h src/*.hpp)

# Leemos todos los archivos de test en ./tests
#file(GLOB TEST_SOURCES tests/*.cpp)

file(GLOB SOURCE_FILES src/Instruccion.cpp src/trie.h src/trie.hpp)
file(GLOB TEST_SOURCES tests/test_trie.cpp)


add_subdirectory(tests/google-test)

# Creamos el ejecutable para correr los tests
add_executable(correrTests ${TEST_SOURCES} ${SOURCE_FILES})

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

add_test(correrTests correrTests)
