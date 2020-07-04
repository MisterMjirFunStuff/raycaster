#include <iostream>
#include <math.h>
#include "constants.h"
#include "game.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 512;

int main(int argc, char* args[])
{
	const int FPS = 60;
  const int frameDelay = 1000 / FPS;

  Uint32 frameStart;
  int frameTime;

  Game::init("SMAE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false);

  while (Game::isRunning())
  {
    frameStart = SDL_GetTicks();

    Game::input();
    Game::update();
    Game::draw();

    frameTime = SDL_GetTicks() - frameStart;

    while (frameDelay > frameTime)
    {
      Game::input();
      // Game::draw();
      frameTime = SDL_GetTicks() - frameStart;
    }
  }

  Game::close();

  return 0;
}
