cmake_minimum_required(VERSION 3.21)
project(ProjektSemestralnyGraTurowa)

set(CMAKE_CXX_STANDARD 23)

add_executable(ProjektSemestralnyGraTurowa UI/main.cpp Creature/Creature.cpp Creature/Creature.hpp Fight/Fight.cpp Fight/Fight.hpp)
