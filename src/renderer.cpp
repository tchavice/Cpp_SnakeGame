#include "renderer.h"
#include <iostream>
#include <string>

//Added: BackgroundImage Constructor
BackgroundImage::BackgroundImage() {
  // initialize image: adapted from fschr/SDL2 image example
  if( !(IMG_Init( IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Error initializing SDL image :" << IMG_GetError() << "\n";
  }
}

//Added: BackgroundImage Load method
void BackgroundImage::Load(SDL_Surface *screenSurface, std::string path) {
  // Obtain surface from file: adapted from fschr/SDL2 image ex
  SDL_Surface *imgSurface = IMG_Load(path.c_str());
  if (imgSurface == nullptr) {
    std::cerr << "Error loading image :" << IMG_GetError() << "\n";
  }
  // Convert surface to screen format
  //SDL_Surface *screenSurface = renderer->GetWindowSurface();
  SDL_Surface *optimizedImg = SDL_ConvertSurface(imgSurface, screenSurface->format, 0);
  if(optimizedImg == NULL) {
    std::cerr << "Error optimizing image :" << SDL_GetError() << "\n";
  }
  SDL_FreeSurface(imgSurface);
  
  SDL_BlitSurface(optimizedImg, NULL, screenSurface, NULL);
  
}

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

  //Create background and load to window
  _background.Load(GetWindowSurface(), kBackgroundPath);
  SDL_UpdateWindowSurface(sdl_window);

}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
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

//Added for background image: get SDL window surface
SDL_Surface* Renderer::GetWindowSurface() {
  SDL_Surface *screenSurface = SDL_GetWindowSurface(sdl_window);
  if(screenSurface == NULL) {
    std::cerr << "Error getting window surface :" << SDL_GetError() << "\n";
   }
   return screenSurface;
}
