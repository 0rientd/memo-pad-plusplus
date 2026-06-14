#include <SDL2/SDL.h>

int renderButton(SDL_Renderer* renderer, int x, int y, int h, int w) {
  SDL_SetRenderDrawColor( renderer, 51, 61, 109, 230 ); // Draw in solid blue

  SDL_Rect r;
  r.x = x;
  r.y = y;
  r.h = h;
  r.w = w;

  return SDL_RenderFillRect(renderer, &r);
}
