#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "sprite.h"

class Button
{
public:
  Button();

  void init(int x, int y, Sprite* path);

  void free();

  void eventHandle(SDL_Event &e);

  void render();

  Sprite* getSprite();

  void setSprite(Sprite* sprite);

private:
  int mPosX, mPosY;

  Sprite* mSprite;
};

#endif
