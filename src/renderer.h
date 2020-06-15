#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <string>
#include "SDL.h"
#include <SDL2/SDL_image.h>  //for background image
#include "snake.h"

class BackgroundImage {
  public:
    BackgroundImage();
    //~BackgroundImage();
    void Load(SDL_Surface *screenSurface, std::string path);

};

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);
  SDL_Surface* GetWindowSurface();  //added: getter for sdl_window surface

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  BackgroundImage _background;    //added: background image class private mbr

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  const std::string kBackgroundPath{"../img/ocean.png"};  //added: img path  
};

#endif