cmake_minimum_required(VERSION 3.24)
project(Console_game)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 23)
add_executable(Console_game main.cpp dialog.h enemy.h layout.h game_config.h game_functions.h)
