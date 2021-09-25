cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# set the project name
project(TicTacToe)

add_executable(
  TicTacToe
  main.cpp
  sprite.cpp
  button.cpp
)

target_link_libraries(TicTacToe PUBLIC SDL2 SDL2_ttf SDL2_image SDL2_mixer)
