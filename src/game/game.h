#ifndef RAYCASTER_GAME
#define RAYCASTER_GAME

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "sdl.h"
#include "game_input.h"
#include "manager.h"
#include "game_object.h"

class Game
{
public:
  static void init(const char* title, int x, int y, int width, int height, bool fullScreen);
  static void close();

  static void input();
  static void update();
  static void draw();

  static bool isRunning();
  static GameInput getInputs();
private:
  Game();
  ~Game();

  static Window* window;
  static bool running;
  static SDL_GLContext glContext;
  static GameInput inputs;
  static Manager manager;
};

#endif
