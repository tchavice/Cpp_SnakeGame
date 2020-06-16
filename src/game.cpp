#include "game.h"
#include <iostream>
#include <thread>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width)),
      random_h(0, static_cast<int>(grid_height)),
      random_interval(0, 500),  //controls how often food randomly moves
      player(std::make_unique<Player>()) {
}

void Game::PlayerMenu() {
  bool repeat = true;
  std::string name;
  char level;
  char start;

  std::cout << "Enter name: ";
  std::cin >> name;
  std::cout << "Welcome " << name << " to the underwater snake game!" << std::endl;
  while(repeat) {
    repeat = false;
    std::cout << "The game has three levels.  Level 1 is the easiest, 3 is the hardest\n";
    std::cout << "Enter 1 2 or 3 to select your level: ";
    std::cin >> level;
    std::cout << "You selected level " << level << std::endl;
    switch(level) {
      case '1':
        std::cout << "This shouldn't be too hard! \n";
        std::cout << "Find the food in the green blocks and your snake will grow big and strong\n";
        std::cout << "But be quick or your food might get away!\n";
        break;
      case '2':
        std::cout << "This will be a little harder...\n";
        std::cout << "Eat the food, but avoid the poison in the red blocks!\n";
        std::cout << "Your snake will shrink if you eat poison, and may disappear\n";
        break;
      case '3':
        std::cout << "Buckle up!\n";
        std::cout << "The poison will kill your snake if you touch it\n";
        break;
      default:
        std::cout << "Invalid level, try again\n";
        repeat = true;
        continue;
    }
  }
  while(true) {
    std::cout << "To start, press s (for snake, of course) \n";
    std::cin >> start;
    if (start == 's') break;
  }

  player->SetName(name);
  player->SetLevel(level);

}

//Added startup function to handle threads for menu, 
void Game::Startup() {
  std::thread t = std::thread(&Game::PlayerMenu, this);
  t.join();
  
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  //Placing food and poison placed in threads to ensure funcs return before render is called
  std::thread t1 = std::thread(&Game::PlaceFood, this); //moved from constructor to run loop, after level is set
  std::thread t2 = std::thread(&Game::PlacePoison, this);
  t1.join();
  t2.join();

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, poison);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    if (!snake.alive) {
      running = false;
      std::cout << "Your snake died - Oh no!\n";
      SDL_Delay(1000);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

// Added: place poison method for levels 2/3
void Game::PlacePoison() {
  int x, y;
  char level = GetLevel();
  if(level == '1') {
    poison.x = -1;
    poison.y = -1;
    return;
  }
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // poison
    if (!snake.SnakeCell(x, y)) {
      poison.x = x;
      poison.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
  // Randomly move the food every so often
  // The probability is controlled by the values of random_interval set in constructor
  else {
    if(random_interval(engine) == 2) PlaceFood();
  }
  //Added: In level 2 and 3, check for poison
  if (GetLevel() == '1') return;
  if (poison.x == new_x && poison.y == new_y) {
    //in level 2, lose a point and shrink the snake
    if (GetLevel() == '2') {
      score--;
      snake.ShrinkBody();
      PlacePoison();
    }
    //in level 3, die
    else snake.alive = false;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
char Game::GetLevel() {return player->GetLevel(); }
std::string Game::GetName() {return player->GetName(); }
bool Game::GetAlive() {return snake.alive; }