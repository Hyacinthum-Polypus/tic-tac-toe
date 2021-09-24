#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "sprite.h"
#include "main.h"

const int SCREEN_WDITH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

Sprite ticTacToe;
Sprite imageO;
Sprite imageX;

bool init()
{
  bool success = true;

  if(!SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("Failed to initalize! SDL Error: %s\n", SDL_GetError());
    success = false;
  }
  else
  {
    gWindow = SDL_CreateWindow("Tic Tac Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WDITH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
      printf("Failed to create window. SDL Errpr: %s\n", SDL_GetError());
      success = false;
    }
    else
    {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if(gRenderer == NULL)
      {
        printf("Failed to create renderer. SDL Error: %s\n", SDL_GetError());
        success = false;
      }
      else
      {
        SDL_SetRenderDrawColor(gRenderer, 1, 1, 1, 1);

        if(!(IMG_Init(IMG_INIT_PNG)|IMG_INIT_PNG))
        {
          printf("Failed to initalize SDL_image. SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }

        if(TTF_Init() < 0)
        {
          printf("Failed to initialize SDL_ttf. SDL_ttf Error: %s\n", TTF_GetError());
          success = false;
        }

        if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
          printf("Failed to initalize SDL_mixer. SDL_mixer Error: %s\n", Mix_GetError());
          success = false;
        }
      }
    }
  }
  return success;
}

bool loadMedia()
{
  bool success = true;
  if(!ticTacToe.loadFromFile("media/tic-tac-toe.png"))
  {
    success = false;
  }

  if(!imageO.loadFromFile("media/o.png"))
  {
    success = false;
  }

  if(!imageX.loadFromFile("media/x.png"))
  {
    success = false;
  }
  return success;
}

void close()
{
  ticTacToe.free();
  imageO.free();
  imageX.free();

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  SDL_Quit();
}

int main()
{
  if(!init())
  {
    printf("Failed to initalize!\n");
  }
  else
  {
    if(!loadMedia())
    {
      printf("Failed to load all media!\n");
    }
    else
    {
      bool quit = false;

      SDL_Event e;

      while(!quit)
      {
        while(SDL_PollEvent(&e) != 0)
        {
          if(e.type == SDL_QUIT)
          {
            quit = true;
          }
        }
        SDL_RenderClear(gRenderer);
        ticTacToe.render(0, 0);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}
