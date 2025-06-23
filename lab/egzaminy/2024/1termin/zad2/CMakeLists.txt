cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Zad2)

# Add the executable for each source file
add_executable(brut2 ./brut.cpp)
add_executable(gen2 ./gen.cpp)
add_executable(zad2 ./zad.cpp)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)