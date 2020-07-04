#ifndef WINDOW
#define WINDOW

#include <SDL2/SDL.h>

class Window
{
public:
  Window(const char* title, int x, int y, int width, int height, bool fullScreen);
  ~Window();
  SDL_Window* getSDL();
private:
  SDL_Window* window;
};

#endif
