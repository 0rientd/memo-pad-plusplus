#include "text.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int position_y(int y, int h, int text_height) {
  return y + (h - text_height) / 2;
}

int position_x(int x, int w, int text_width) {
  return x + (w - text_width) / 2;
}

void renderButtonBorder(SDL_Renderer* renderer, int x, int y, int h, int w) {
  SDL_SetRenderDrawColor(renderer, 51, 61, 109, 200);
  
  // top line
  SDL_RenderDrawLine(renderer, x - 1, y - 1, x + w, y - 1);
  
  // left line
  SDL_RenderDrawLine(renderer, x - 1, y - 1, x - 1, y + h);
  
  // bottom line
  SDL_RenderDrawLine(renderer, x - 1, y + h, x + w, y + h);
  
  // right line
  SDL_RenderDrawLine(renderer, x + w, y, x + w, y + h);
}

void renderButtonShadow(SDL_Renderer* renderer, int x, int y, int h, int w) {
  SDL_SetRenderDrawColor(renderer, 34, 34, 34, 150);
  
  for (int i = 0; i < 3; i++) {
    // left line
    SDL_RenderDrawLine(renderer, x - 2 - i, y + i, x - 2 - i, y + h + i);

    // bottom line
    SDL_RenderDrawLine(renderer, x - 2 - i, y + h + i, x + w - 2, y + h + i);
  }
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
  renderButtonBorder(renderer, x, y, h, w);
  renderButtonShadow(renderer, x, y, h, w);

  TTF_SizeText(font, text, &text_width, &text_height);
  renderTextInput(renderer, font, text, position_x(x, w, text_width), position_y(y, h, text_height));
  
  return 0;
}
