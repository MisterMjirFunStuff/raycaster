cmake_minimum_required(VERSION 3.10)

project(raycaster)

add_executable(raycaster
  src/main.cpp

  src/caster.cpp
  src/level.cpp

  src/characters/player.cpp
  src/characters/bullet.cpp

  src/game/game.cpp
  src/game/manager/manager.cpp

  src/sdl/renderer.cpp
  src/sdl/texture.cpp
  src/sdl/window.cpp
)

target_include_directories(raycaster PUBLIC
  src
  src/characters
  src/game
  src/game/manager
  src/game/object
  src/sdl
)

target_link_libraries(raycaster glfw GL GLEW SDL2 SDL2_image)

set_target_properties(raycaster PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
