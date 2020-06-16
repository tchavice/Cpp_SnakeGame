#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include <SDL2/SDL_image.h>  //for background image
#include "snake.h"


class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, SDL_Point const &poison);
  void UpdateWindowTitle(int score, int fps);
  
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *background;    //added: background member, load_background method
  SDL_Texture* load_background(const std::string path, SDL_Renderer* sdl_renderer);
  

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  const std::string kBackgroundPath{"../img/ocean.png"};  //added: img path  
};

#endif