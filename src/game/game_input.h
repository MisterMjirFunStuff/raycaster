#ifndef RAYCASTER_GAME_INPUT
#define RAYCASTER_GAME_INPUT

#include "sdl.h"

struct GameInput
{
  // Key maps
  int upKey, downKey, leftKey, rightKey, shootKey;
  // Key state
  bool up, down, left, right, shoot;
  // Mouse pos
  int mouseX, mouseY;
};

#endif
