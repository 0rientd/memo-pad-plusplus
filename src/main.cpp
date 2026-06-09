#include <iostream>
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

using namespace std;

void renderTextInput(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y) {
  SDL_Color color = {255, 255, 255, 255}; // white
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
}

int main() {
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

  bool running = true;
  vector<string> inputText;
  inputText.push_back("");

  while (running) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        inputText.push_back("");
 //       default_y_output += 20;
      } else if (event.type == SDL_TEXTINPUT) {
        inputText.back() += event.text.text;
        // cout << "Input: " << inputText << endl;
      } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && inputText.size()) {

        if (!inputText.empty() &&
            !inputText.back().empty())
        {
            inputText.back().pop_back();
        }

      } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && !inputText.size()) {
        cout << "Tentando apagar ultima linha.. Era para ir para a linha de cima." << endl;

      } else if (event.type == SDL_QUIT) {
          running = false;
      }
    }

    SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
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
