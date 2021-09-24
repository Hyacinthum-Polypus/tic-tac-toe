#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <SDL2/SDL.h>

class Sprite
{
public:
  Sprite();

  ~Sprite();

  void free();

  bool loadFromFile(std::string path);

  bool loadFromRenderedText(std::string textTexture, SDL_Color textColor);

  void render(int x, int y);

  int getWidth();

  int getHeight();

private:
  SDL_Texture* mTexture;
  int mWidth, mHeight;
};

#endif
