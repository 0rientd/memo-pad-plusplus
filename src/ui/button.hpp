#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void renderButton(
  SDL_Renderer* renderer,
  TTF_Font* font,
  const char* text,
  int x,
  int y, 
  int h,
  int w
);
