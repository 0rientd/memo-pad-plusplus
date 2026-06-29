#include "text.hpp"

#include <iostream>

using namespace std;

int calcLineLength(SDL_Renderer* renderer, TTF_Font* font, const char* text) {
  if (!text || !*text) {
    return 0;
  }

  SDL_Color color = {51, 61, 109, 255};

  SDL_Surface* surface2 = TTF_RenderText_Blended(font, text, color);

  if (!surface2) {
    cerr << "TTF_RenderText_Blended Error: " << TTF_GetError() << std::endl;
    return 1;
  }

  SDL_Texture* texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

  if (!texture2) {
    cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
    SDL_FreeSurface(surface2);
    return 1;
  }

  return surface2->w;
}

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
