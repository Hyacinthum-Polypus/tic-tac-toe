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

bool yourTurn = true;

const int BUTTON_TOTAL = 9;
Button buttons[BUTTON_TOTAL];

void aiTurn();

enum winState
{
  NO_WINNER,
  PLAYER_WINNER,
  BOT_WINNER
};

winState checkWinState();

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

      SDL_Event e;

      SDL_Color black = {0,0,0,255};

      for (size_t i = 0; i < BUTTON_TOTAL; i++) {
        int x = i / 3;
        int y = i % 3;
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
        if(checkWinState() == NO_WINNER)
        {
          if(yourTurn)
          {
            turnTexture.loadFromRenderedText("Your Turn...", black);
          }
          else
          {
            turnTexture.loadFromRenderedText("Their Turn...", black);
          }
        }

        if(checkWinState() == PLAYER_WINNER)
        {
          turnTexture.loadFromRenderedText("You Win!!!", black);
        }
        else if(checkWinState() == BOT_WINNER)
        {
          turnTexture.loadFromRenderedText("Bot Wins!!!", black);
        }

        SDL_RenderClear(gRenderer);
        ticTacToeTexture.render(0, 0);
        for (size_t i = 0; i < BUTTON_TOTAL; i++) {
          buttons[i].render();
        }
        turnTexture.render(0, 280);
        SDL_RenderPresent(gRenderer);

        //AI
        if(!yourTurn && checkWinState() == NO_WINNER)
        {
          aiTurn();
        }
        //checkWinState after AI turn

      }
    }
  }
  close();
  return 0;
}

void aiTurn()
{
  SDL_Delay(500);
  while(!yourTurn)
  {
    int i = rand() % 9;
    if(buttons[i].getSprite() == &blankTexture)
    {
      buttons[i].setSprite(&oTexture);
      yourTurn = true;
    }
  }
}

winState checkWinState()
{
  winState currentWinState = NO_WINNER;

  //Check if player winner
  for (size_t x = 0; x < 3; x++) {
    if(buttons[x].getSprite() == &xTexture)
    {
      if(buttons[x+3].getSprite() == &xTexture)
      {
        if(buttons[x+6].getSprite() == &xTexture)
        {
          currentWinState = PLAYER_WINNER;
        }
      }
    }
  }

  for (size_t y = 0; y < 3; y++) {
    if(buttons[y*3].getSprite() == &xTexture)
    {
      if(buttons[y*3+1].getSprite() == &xTexture)
      {
        if(buttons[y*3+2].getSprite() == &xTexture)
        {
          currentWinState = PLAYER_WINNER;
        }
      }
    }
  }

  if(buttons[4].getSprite() == &xTexture)
  {
    if(buttons[0].getSprite() == &xTexture)
    {
      if(buttons[8].getSprite() == &xTexture)
      {
        currentWinState = PLAYER_WINNER;
      }
    }
    if(buttons[2].getSprite() == &xTexture)
    {
      if(buttons[6].getSprite() == &xTexture)
      {
        currentWinState = PLAYER_WINNER;
      }
    }
  }


  //Check if AI winner
  for (size_t x = 0; x < 3; x++) {
    if(buttons[x].getSprite() == &oTexture)
    {
      if(buttons[x+3].getSprite() == &oTexture)
      {
        if(buttons[x+6].getSprite() == &oTexture)
        {
          currentWinState = BOT_WINNER;
        }
      }
    }
  }

  for (size_t y = 0; y < 3; y++) {
    if(buttons[y*3].getSprite() == &oTexture)
    {
      if(buttons[y*3+1].getSprite() == &oTexture)
      {
        if(buttons[y*3+2].getSprite() == &oTexture)
        {
          currentWinState = BOT_WINNER;
        }
      }
    }
  }

  if(buttons[4].getSprite() == &oTexture)
  {
    if(buttons[0].getSprite() == &oTexture)
    {
      if(buttons[8].getSprite() == &oTexture)
      {
        currentWinState = BOT_WINNER;
      }
    }
    if(buttons[2].getSprite() == &oTexture)
    {
      if(buttons[6].getSprite() == &oTexture)
      {
        currentWinState = BOT_WINNER;
      }
    }
  }

  return currentWinState;
}
