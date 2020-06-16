#include "renderer.h"
#include <iostream>
#include <string>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  //Added: Create background and load to window
  if(background == NULL) {
    background = load_background(kBackgroundPath, sdl_renderer);
  }

}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Point const &poison) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  //SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF); //Removed
  SDL_RenderClear(sdl_renderer);
  // Added: copy background to window
  SDL_RenderCopy(sdl_renderer, background, NULL, NULL);

  // Render food using green blocks
  SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xFF, 0x00, 0x00);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Added: render poison using red blocks
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0x00);
  block.x = poison.x * block.w;
  block.y = poison.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

//Added: load background image
SDL_Texture* Renderer::load_background(const std::string path, SDL_Renderer* sdl_renderer) {
  // Obtain surface from file: adapted from fschr/SDL2 image ex
  SDL_Surface *imgSurface = IMG_Load(path.c_str());
  if (imgSurface == nullptr) {
    std::cerr << "Error loading image :" << IMG_GetError() << "\n";
  }
  // Create texture from the image to be applied to the window
  SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(sdl_renderer, imgSurface);
  if(imgTexture == NULL) {
    std::cerr << "Error loading texture :" << SDL_GetError() << "\n";
  }
  // Clean up memory
  SDL_FreeSurface(imgSurface);
  
  return imgTexture;
  
}
