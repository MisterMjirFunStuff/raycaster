#ifndef RENDERER
#define RENDERER

#include <SDL2/SDL.h>
#include "window.h"

class Texture;

class Renderer
{
public:
  Renderer(Window*);
  ~Renderer();

  void present();
  void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
  void clear();
  void fillRect(SDL_Rect* destRect);
  void copy(Texture*, SDL_Rect* srcRect, SDL_Rect* destRect);
  void copy(Texture*, SDL_Rect* srcRect, SDL_Rect* destRect, double angle);
  void setAlpha(Texture*, Uint8);
  SDL_Renderer* getSDL();
private:
  SDL_Renderer* renderer;
};

#endif
