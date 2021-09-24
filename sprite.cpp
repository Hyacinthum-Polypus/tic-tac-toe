#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sprite.h"
#include "main.h"

Sprite::Sprite()
{
  mWidth = 0;
  mHeight = 0;
  mTexture = NULL;
}

Sprite::~Sprite()
{
  free();
}

void Sprite::free()
{
  mWidth = 0;
  mHeight = 0;
  SDL_DestroyTexture(mTexture);
  mTexture = NULL;
}

bool Sprite::loadFromFile(std::string path)
{
  free();
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == NULL)
  {
    printf("Failed to load %s. SDL_image Error: %s\n", IMG_GetError());
  }
  else
  {
    SDL_SetColorKey(loadedSurface, SDL_FALSE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if(mTexture == NULL)
    {
      printf("Failed to create texture from surface. SDL Error: %s\n", SDL_GetError());
    }
    else
    {
      mWidth = loadedSurface->w;
      mHeight = loadedSurface->h;
    }
    SDL_FreeSurface(loadedSurface);
  }
  return mTexture != NULL;
}

bool Sprite::loadFromRenderedText(std::string textTexture, SDL_Color textColor)
{
  free();
  return 0;
}

void Sprite::render(int x, int y)
{
  SDL_Rect mRect = {x, y, mWidth, mHeight};

  SDL_RenderCopy(gRenderer, mTexture, NULL, &mRect);
}

int Sprite::getWidth()
{
  return mWidth;
}

int Sprite::getHeight()
{
  return mHeight;
}
