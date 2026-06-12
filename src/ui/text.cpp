#include "text.hpp"

#include <iostream>

using namespace std;

void renderTextInput(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
  SDL_Color color = {51, 61, 109, 255};
  SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);

  if (!surface) {
    cerr << "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
    return;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (!texture) {
    cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surface);
    return;
  }

  SDL_Rect dest = { x, y, surface->w, surface->h };

  SDL_RenderCopy(renderer, texture, NULL, &dest);

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
};
