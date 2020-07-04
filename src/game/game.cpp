#include "game.h"
#include <iostream>

#include "player.h"
#include "level.h"
#include "caster.h"

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 512;

Window* Game::window;
bool Game::running = true;
SDL_GLContext Game::glContext;
GameInput Game::inputs = {SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDL_BUTTON_LEFT, false, false, false, false, false, 0, 0};
Manager Game::manager;

void Game::init(const char* title, int x, int y, int width, int height, bool fullScreen)
{
  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    running = false;
    return;
  }

  window = new Window(title, x, y, width, height, fullScreen);
  glContext = SDL_GL_CreateContext(window->getSDL());

  /* Initialize OpenGL stuff */
  if (GLEW_OK != glewInit())
	{
		std::cout << "GLEW could not initialize" << std::endl;
    running = false;
		return;
	}

  /* Set stuff up for the window */
	glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1, 1);

  /* Object Stuff */
  manager.objects.push_back(new Level());
  if (dynamic_cast<Level*>(manager.objects[0])->load("res/lvl_1.rdata"))
  {
    std::cout << "The level couldn't be loaded" << std::endl;
		return;
  }
  manager.objects.push_back(new Player(240, 256, dynamic_cast<Level*>(manager.objects[0])));
  manager.objects.push_back(new Caster(dynamic_cast<Level*>(manager.objects[0]), dynamic_cast<Player*>(manager.objects[1])));
}

void Game::close()
{
  SDL_GL_DeleteContext(glContext);
  SDL_Quit();
}

void Game::input()
{
  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    switch (e.type)
    {
      case SDL_QUIT:
        running = false;
        break;
      case SDL_KEYDOWN:
      {
        int key = e.key.keysym.sym;
        if (key == inputs.upKey)
        {
          inputs.up = true;
        }
        if (key == inputs.downKey)
        {
          inputs.down = true;
        }
        if (key == inputs.leftKey)
        {
          inputs.left = true;
        }
        if (key == inputs.rightKey)
        {
          inputs.right = true;
        }
        break;
      }
      case SDL_KEYUP:
      {
        int key = e.key.keysym.sym;
        if (key == inputs.upKey)
        {
          inputs.up = false;
        }
        if (key == inputs.downKey)
        {
          inputs.down = false;
        }
        if (key == inputs.leftKey)
        {
          inputs.left = false;
        }
        if (key == inputs.rightKey)
        {
          inputs.right = false;
        }
        break;
      }
      case SDL_MOUSEBUTTONDOWN:
        switch (e.button.button)
        {
          case SDL_BUTTON_LEFT:
            inputs.shoot = true;
            break;
        }
      break;
    }
  }

  SDL_GetMouseState(&inputs.mouseX, &inputs.mouseY);
}

void Game::update()
{
  manager.update();

  inputs.shoot = false;
}

void Game::draw()
{
  glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	manager.draw();

  SDL_GL_SwapWindow(window->getSDL());
}

bool Game::isRunning()
{
  return running;
}

GameInput Game::getInputs()
{
  return inputs;
}
