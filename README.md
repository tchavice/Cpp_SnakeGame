# CPPND: Capstone Snake Game, with great new features

This is an enhanced version of the starter repo provided for the capstone project of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Rubric Items
### Loops Functions and IO
|Criteria| How is it satisfied | Where |
| --- | --- | ---|
|The project demonstrates an understanding of C++ functions and control structures.| The game additions use functions and various control flow structures.| ex: game.cpp TODO|
|The project reads data from a file and process the data, or the program writes data to a file.| The updated game reads in a background image using the SDL image library and applies it to the background of the game | renderer.cpp # TODO |
|The project accepts user input and processes the input.| The startup menu launches the game based on user input | TODO |

### Object Oriented Programming
|Criteria| How is it satisfied | Where |
| --- | --- | ---|
|The project uses Object Oriented Programming techniques.| New classes are implemented, and the functionality of existing classes is expanded| game.h Player class|
|Classes use appropriate access specifiers for class members.| Classes use access specifiers | game.h Player class|
|Classes abstract implementation details from their interfaces.| Classes are documented through comments or function names | eg game.h Player class|
|Classes encapsulate behavior.| Class members are private, accessed via public functions| game.h Player class|


### Memory Management
|Criteria| How is it satisfied | Where |
| --- | --- | ---|
|The project uses smart pointers instead of raw pointers.| Game class includes smart pointer to player class| game.h #28|

### Concurrency
|Criteria| How is it satisfied | Where |
| --- | --- | ---|
|The project uses multithreading.| Startup function uses threads to manage player menu and other functions | game.cpp TODO|

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* Additional SDL2 Libraries
  * SDL_image
  * Installation instructions can be found [here](http://www.sdltutorials.com/sdl-image)
  * in Ubuntu: sudo apt-get install libsdl2-image-dev
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.