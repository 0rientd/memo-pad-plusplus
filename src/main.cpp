#include "ui/text.hpp"
#include "ui/button.hpp"

#include <string>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_clipboard.h>

using namespace std;

void copyAllStrings(vector<string> inputText) {
  string text_to_clipboard;

  for (long unsigned int i = 0; i < inputText.size(); i++) {
    text_to_clipboard += inputText[i] + "\n";
  }

  int result = SDL_SetClipboardText(text_to_clipboard.c_str());
  if (result != 0) {
    cout << "Error in clipboard" << endl;
  }
}

char * getAllClipboardStrings() {
  // to-do get the strings with new lines
  return SDL_GetClipboardText();
}

vector<string> clearAllStrings(vector<string> inputText) {
  inputText.clear();
  inputText.push_back("");

  return inputText;
}

vector<string> clearLastInput(vector<string> inputText) {
  if (!inputText.back().empty()) {
      inputText.back().pop_back();
  } else {
    if (inputText.size() > 1) {
      inputText.pop_back();
    }
  }

  return inputText;
}


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

  SDL_Window* window = SDL_CreateWindow("Memo-Pad++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 450, SDL_WINDOW_SHOWN);
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
    int y = 20;

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_TEXTINPUT) {
        inputText.back() += event.text.text;

        if (calcLineLength(renderer, font, inputText.back().c_str()) > 430) {
          std::string lastVector = inputText.back();

          char lastCharacter = lastVector.back();

          inputText.back().pop_back();
          inputText.push_back(std::string(1, lastCharacter));
        }

      } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN) {
        inputText.push_back("");

      } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && inputText.size()) {
        inputText = clearLastInput(inputText);

      } else if (event.type == SDL_KEYDOWN ) {
        if (event.key.keysym.sym == SDLK_n && (event.key.keysym.mod & KMOD_CTRL)) {
          inputText = clearAllStrings(inputText);

        } else if (event.key.keysym.sym == SDLK_q && (event.key.keysym.mod & KMOD_CTRL)) {
          running = false;

        } else if (event.key.keysym.sym == SDLK_c && (event.key.keysym.mod & KMOD_CTRL)) {
          copyAllStrings(inputText);   

        } else if (event.key.keysym.sym == SDLK_v && (event.key.keysym.mod & KMOD_CTRL)) {
          inputText.push_back(getAllClipboardStrings());

        }
      } else if (event.type == SDL_QUIT) {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 255, 240, 217, 220);
    SDL_RenderClear(renderer);

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

    renderButton(renderer, font, "ctrl+n", 35, 400, 25, 100);
    renderButton(renderer, font, "ctrl+c", 145, 400, 25, 100);
    renderButton(renderer, font, "ctrl+v", 255, 400, 25, 100);
    renderButton(renderer, font, "ctrl+q", 365, 400, 25, 100);

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
