#include "text.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int position_x(int x, int y) {
  int position = 0;

  return position;
}

int renderButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, int h, int w) {
  SDL_SetRenderDrawColor(renderer, 255, 207, 149, 200);

  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.h = h;
  r.w = w;

  SDL_RenderFillRect(renderer, &r);

  renderTextInput(renderer, font, text, x+(h/4), y);
  return 0;
}
