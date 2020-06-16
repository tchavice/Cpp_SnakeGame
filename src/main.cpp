#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Game game(kGridWidth, kGridHeight);
  game.Startup();   //Added startup menu
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  game.Run(controller, renderer, kMsPerFrame);

  // Print personalized game summary
  //std::cout << "Game has terminated successfully!\n";
  if(game.GetAlive()){
    std::cout << "Congratulations " << game.GetName() << " your snake lived!\n";
  }
  else std::cout << "RIP snake of " << game.GetName() << "\n";
  std::cout << "You scored " << game.GetScore() << " on level " << game.GetLevel() << "\n";
  std::cout << "Your snake was " << game.GetSize() << " feet long\n";
  //std::cout << "Score: " << game.GetScore() << "\n";
  //std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}