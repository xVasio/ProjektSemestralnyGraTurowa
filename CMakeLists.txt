cmake_minimum_required(VERSION 3.16.3)
project(ProjektSemestralnyGraTurowa)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined,float-divide-by-zero,address,leak")
add_executable(ProjektSemestralnyGraTurowa UI/main.cpp Creature/Creature.cpp Fight/Fight.cpp SpecialAbility/SpecialAbility.cpp Game/Game.cpp)
target_include_directories(ProjektSemestralnyGraTurowa PUBLIC Hpp)

