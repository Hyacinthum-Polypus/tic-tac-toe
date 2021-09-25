#include <stdio.h>
#include <string>
#include "button.h"
#include "sprite.h"
#include "main.h"

Button::Button()
{
  mPosX = 0;
  mPosY = 0;

  mSprite = NULL;
}

void Button::init(int x, int y, Sprite* sprite)
{
  mPosX = x;
  mPosY = y;

  mSprite = sprite;
}


void Button::free()
{
  mPosX = 0;
  mPosY = 0;
  mSprite = NULL;
}

void Button::eventHandle(SDL_Event &e)
{
  if(e.type == SDL_MOUSEBUTTONDOWN)
  {
    int x = 0, y = 0;
    SDL_GetMouseState(&x, &y);
    bool mouseOver = true;
    if(x < mPosX)
    {
      mouseOver = false;
    }

    if(x > mPosX + mSprite->getWidth())
    {
      mouseOver = false;
    }

    if(y < mPosY)
    {
      mouseOver = false;
    }

    if(y > mPosY + mSprite->getHeight())
    {
      mouseOver = false;
    }

    if(mouseOver)
    {
      if(mSprite == &blankTexture)
      {
        mSprite = &xTexture;
        yourTurn = false;
      }
    }
    else
    {
      printf("Button Not Pressed!\n");
    }
  }
}

void Button::render()
{
  mSprite->render(mPosX, mPosY);
}

Sprite* Button::getSprite()
{
  return mSprite;
}

void Button::setSprite(Sprite* sprite)
{
  mSprite = sprite;
}
