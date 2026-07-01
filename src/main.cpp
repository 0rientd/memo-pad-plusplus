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

void renderCurrentChar(SDL_Renderer* renderer, TTF_Font* font, int windowWidth, const char* text, int y) {
  int lineLength = calcLineLength(renderer, font, text);


  SDL_SetRenderDrawColor(renderer, 51, 61, 109, 200);
  SDL_Rect r;
  r.x = lineLength + 10;
  r.y = y + 3;
  r.h = 18;
  r.w = 10;

  if (lineLength > windowWidth - 20) {
    return;
  }

  SDL_RenderFillRect(renderer, &r);
}

int main() {
  bool running = true;
  vector<string> inputText = { "" };
  int windowWidth = 500;
  int windowHeight = 450;

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

  SDL_Window* window = SDL_CreateWindow("Memo-Pad++", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
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

    int coordinate_y = 20;

    while (SDL_PollEvent(&event)) {
      SDL_GetRendererOutputSize(renderer, &windowWidth, &windowHeight);

      if (event.type == SDL_TEXTINPUT) {
        inputText.back() += event.text.text;

        if (calcLineLength(renderer, font, inputText.back().c_str()) > windowWidth - 10) {
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

    unsigned int cursorIndex = 1;
    for (const auto& line : inputText) {
      if(cursorIndex == inputText.size()) {
        renderCurrentChar(renderer, font, windowWidth, line.c_str(), coordinate_y);
      }

      if (!line.empty()) {
        renderTextInput(
          renderer,
          font,
          line.c_str(),
          10,
          coordinate_y 
        );
      }

      coordinate_y += 25;
      cursorIndex++;
    }

    renderButton(renderer, font, "ctrl+n", (windowWidth - 500) +  35 - (windowWidth - 500) / 2, windowHeight - 50, 25, 100);
    renderButton(renderer, font, "ctrl+c", (windowWidth - 500) + 145 - (windowWidth - 500) / 2, windowHeight - 50, 25, 100);
    renderButton(renderer, font, "ctrl+v", (windowWidth - 500) + 255 - (windowWidth - 500) / 2, windowHeight - 50, 25, 100);
    renderButton(renderer, font, "ctrl+q", (windowWidth - 500) + 365 - (windowWidth - 500) / 2, windowHeight - 50, 25, 100);

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
