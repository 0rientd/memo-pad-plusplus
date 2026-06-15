#include "text.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int position_y(int y, int h, int text_height) {
  return y + (h - text_height) / 2;
}

int position_x(int x, int w, int text_width) {
  return x + (w - text_width) / 2;
}

int renderButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, int h, int w) {
  int text_width = 0, text_height = 0;

  SDL_SetRenderDrawColor(renderer, 255, 207, 149, 200);
  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.h = h;
  r.w = w;
  SDL_RenderFillRect(renderer, &r);

  TTF_SizeText(font, text, &text_width, &text_height);
  renderTextInput(renderer, font, text, position_x(x, w, text_width), position_y(y, h, text_height));
  
  return 0;
}
