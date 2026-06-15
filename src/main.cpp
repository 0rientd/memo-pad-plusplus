#include "ui/text.hpp"
#include "ui/button.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

int main() {
  bool running = true;
  vector<string> inputText = { "" };

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
    
    return 1;
  }

  if (TTF_Init() == -1) {
    std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;

    SDL_Quit();
    return 1;
  }

  TTF_Font* font = TTF_OpenFont("assets/font.ttf", 18);
  if (!font) {
    std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;

    TTF_Quit();
    SDL_Quit();

    return 1;
  }

  SDL_Window* window = SDL_CreateWindow("Memo-Pad++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 600, SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;

    SDL_Quit();
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_StartTextInput();

  while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_TEXTINPUT) {
        inputText.back() += event.text.text;

      } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        inputText.push_back("");

      } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && inputText.size()) {
        if (!inputText.back().empty()) {
            inputText.back().pop_back();
        } else {
          if (inputText.size() > 1) {
            inputText.pop_back();
          }
        }
      } else if (event.type == SDL_KEYDOWN ) {
        if (event.key.keysym.sym == SDLK_n && (event.key.keysym.mod & KMOD_CTRL)) {
          inputText.clear();
          inputText.push_back("");
        }
      } else if (event.type == SDL_QUIT) {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 255, 240, 217, 220);
    SDL_RenderClear(renderer);
    
    int y = 20;

    for (const auto& line : inputText) {
      if (!line.empty()) {
        renderTextInput(
            renderer,
            font,
            line.c_str(),
            10,
            y
        );
      }

      y += 25;
    }

    renderButton(renderer, font, "Teste", 75, 500, 25, 100);

    SDL_RenderPresent(renderer);
  }

  TTF_CloseFont(font);
  TTF_Quit();
  SDL_StopTextInput();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
