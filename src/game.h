#ifndef GAME_H
#define GAME_H

#include <random>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

//Forward declarations
class Player;
class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  std::string GetName();
  char GetLevel();
  bool GetAlive();
  void Startup();
  void PlayerMenu();

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point poison;   //Added: poison member for level 2/3
  std::unique_ptr<Player> player; //Added: player member

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::uniform_int_distribution<int> random_interval;

  int score{0};

  void PlaceFood();
  void PlacePoison();
  void Update();
};

//Create Player class to store player information
class Player {
  public: 
    std::string GetName() {return _name; }
    void SetName(std::string name) {_name = name; }
    char GetLevel() {return _level; }
    void SetLevel(char level) {_level = level; }
  private:
    std::string _name;
    int _score;
    char _level;
};

#endif