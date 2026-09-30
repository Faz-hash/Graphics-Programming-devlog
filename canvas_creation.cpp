#include <iostream>
#include <SDL2/SDL.h>
#include <cstdint>
#include <vector>

const int WIDTH=400;
const int HEIGHT=400;

int main(int argc,char* argv[]){

  int pixelCount = WIDTH * HEIGHT;
  
  SDL_Window* window=SDL_CreateWindow(
    "Basic Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WIDTH,
    HEIGHT,
    SDL_WINDOW_SHOWN
  );

  SDL_Renderer* canvas=SDL_CreateRenderer(
    window,-1,SDL_RENDERER_ACCELERATED
  );

  SDL_Texture* texture_slot=SDL_CreateTexture(
    canvas,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    WIDTH,
    HEIGHT
  );

  std::vector<uint32_t> pixels(pixelCount);

  for(int i=0;i<pixelCount;++i){
    pixels[i]=0xffac7e6e;
  }

  bool isRunning=true;
  SDL_Event event;

  while(isRunning){

    while(SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
          isRunning = false;
      }
    }

    SDL_UpdateTexture(texture_slot,NULL,pixels.data(),WIDTH*sizeof(uint32_t));
    SDL_RenderClear(canvas);
    SDL_RenderCopy(canvas,texture_slot,NULL,NULL);
    SDL_RenderPresent(canvas);
    
  }
  SDL_DestroyTexture(texture_slot);
  SDL_DestroyRenderer(canvas);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}