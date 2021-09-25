#include <string>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
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
    printf("Failed to load %s. SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
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
  SDL_Surface* loadedSurface = TTF_RenderText_Solid(gFont, textTexture.c_str(), textColor);
  if(loadedSurface == NULL)
  {
    printf("Failed to render text to surface. SDL_ttf Error: %s\n", TTF_GetError());
  }
  else
  {
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
