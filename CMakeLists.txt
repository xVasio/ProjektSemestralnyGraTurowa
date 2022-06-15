cmake_minimum_required(VERSION 3.21)
project(ProjektSemestralnyGraTurowa)

set(CMAKE_CXX_STANDARD 23)

add_executable(ProjektSemestralnyGraTurowa UI/main.cpp Creature/Creature.cpp Fight/Fight.cpp SpecialAbility/SpecialAbility.cpp Game/Game.cpp)
target_include_directories(ProjektSemestralnyGraTurowa PUBLIC Hpp)