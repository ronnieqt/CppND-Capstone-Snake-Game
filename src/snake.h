#ifndef SNAKE_H
#define SNAKE_H

#include <SDL_rect.h>
#include <vector>

// STUDENT CODE: forward declaration to avoid include cycle
class Game;

class Snake
{
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(Game* game, int grid_width, int grid_height)
    : game(game)
    , grid_width(grid_width)
    , grid_height(grid_height)
    , head_x(grid_width / 2.0)
    , head_y(grid_height / 2.0)
  {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

private:
  void UpdateHead();
  void UpdateBody(SDL_Point& curr_cell, SDL_Point& prev_cell);

  Game* game;  // STUDENT CODE
  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif
