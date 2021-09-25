#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "sprite.h"
#include "main.h"
#include "button.h"

const int SCREEN_WDITH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;

Sprite ticTacToeTexture;
Sprite oTexture;
Sprite xTexture;
Sprite blankTexture;
Sprite turnTexture;

const int BUTTON_TOTAL = 9;
Button buttons[BUTTON_TOTAL];

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
        SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

        if(!(IMG_Init(IMG_INIT_PNG)|IMG_INIT_PNG))
        {
          printf("Failed to initalize SDL_image. SDL_image Error: %s\n", IMG_GetError());
          success = false;
        }

        if(TTF_Init() == -1)
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

  gFont = TTF_OpenFont("media/WorkSans-VariableFont_wght.ttf", 28);
  if(gFont == NULL)
  {
    printf("Failed to load WorkSans as the global font. SDL_ttf Error: %s\n", TTF_GetError());
    success = false;
  }
  else
  {
      SDL_Color black = {0,0,0,255};
      if(!turnTexture.loadFromRenderedText("Your Turn...", black))
      {
        success = false;
      }
  }

  if(!ticTacToeTexture.loadFromFile("media/tic-tac-toe.png"))
  {
    success = false;
  }

  if(!oTexture.loadFromFile("media/o.png"))
  {
    success = false;
  }

  if(!xTexture.loadFromFile("media/x.png"))
  {
    success = false;
  }

  if(!blankTexture.loadFromFile("media/blank.png"))
  {
    success = false;
  }

  return success;
}

void close()
{
  ticTacToeTexture.free();
  oTexture.free();
  xTexture.free();
  blankTexture.free();

  TTF_CloseFont(gFont);
  gFont = NULL;

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

      bool yourTurn = true;

      SDL_Event e;

      for (size_t i = 0; i < BUTTON_TOTAL; i++) {
        int x = i / 3;
        int y = i % 3;
        //printf("%d, %d, %d\n", i, x, y);
        buttons[i].init(x * 120, y * 90, &blankTexture);
      }
      while(!quit)
      {
        while(SDL_PollEvent(&e) != 0)
        {
          if(e.type == SDL_QUIT)
          {
            quit = true;
          }

          if(yourTurn)
          {
            for (size_t i = 0; i < BUTTON_TOTAL; i++) {
              buttons[i].eventHandle(e);
            }
          }
        }
        SDL_RenderClear(gRenderer);
        ticTacToeTexture.render(0, 0);
        for (size_t i = 0; i < BUTTON_TOTAL; i++) {
          buttons[i].render();
        }
        turnTexture.render(0, 280);
        SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
  return 0;
}
