#ifndef TEXTURE
#define TEXTURE

#include <SDL2/SDL.h>

class Renderer;

class Texture
{
public:
  Texture(Renderer*, const char*);
  ~Texture();
  SDL_Texture* getSDL();
private:
  SDL_Texture* texture;
};

#endif
