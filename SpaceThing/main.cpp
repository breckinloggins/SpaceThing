//
//  main.cpp
//  SpaceThing
//
//  Created by Breckin Loggins on 8/9/14.
//  Copyright (c) 2014 Breckin Loggins. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

int main(int argc, const char * argv[])
{

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "SDL init error: " << SDL_GetError() << std::endl;
    return 1;
  }
  
  SDL_Window *win = SDL_CreateWindow("SpaceThing", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
  if (win == nullptr) {
    std::cout << "SDL create window error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == nullptr) {
    SDL_DestroyWindow(win);
    std::cout << "SDL create renderer error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  char * basePath = SDL_GetBasePath();
  std::string imagePath = std::string(basePath) + "Assets/farback.gif";
  std::cout << "Image path is: " << imagePath << std::endl;
  
  SDL_Surface *bg = IMG_Load(imagePath.c_str());
  if (bg == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL load bmp error loading background: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  SDL_free(basePath);
  
  SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bg);
  SDL_FreeSurface(bg);
  if (tex == nullptr) {
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    std::cout << "SDL create background texture error: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }
  
  int w, h;
  SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
  
  SDL_Event e;
  bool quit = false;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) {
        quit = true;
      }
    }
    
    // Render the scene
    SDL_RenderClear(ren);
    SDL_Rect dst;
    dst.x = 0;
    dst.y = 0;
    dst.w = w;
    dst.h = h;
    SDL_RenderCopy(ren, tex, nullptr, &dst);
    SDL_RenderPresent(ren);
  }
  
  SDL_DestroyTexture(tex);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  
  std::cout << "SDL Sample Exiting\n";
    return 0;
}

