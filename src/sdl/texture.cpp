#include "texture.h"
#include <SDL2/SDL_image.h>
#include "renderer.h"

Texture::Texture(Renderer* ren, const char* fileName)
{
  SDL_Surface* tempSurface = IMG_Load(fileName);
  texture = SDL_CreateTextureFromSurface(ren->getSDL(), tempSurface);
  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  SDL_FreeSurface(tempSurface);
}

Texture::~Texture()
{
  SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::getSDL()
{
  return texture;
}
