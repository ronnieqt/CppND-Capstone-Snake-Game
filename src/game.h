#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <vector>
#include "obstacle.h"
#include "snake.h"
#include "controller.h"
#include "renderer.h"
#include "scoreboard.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height, int nb_obstacles);
  ~Game();

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  int GetScore() const;
  int GetSize() const;
  std::string GetUsername() const;

  bool ObstacleCell(int x, int y) const;  // STUDENT CODE

private:
  Snake snake;
  SDL_Point food;
  // STUDENT CODE (begin)
  std::unique_ptr<Scoreboard> scoreboard;
  int nb_obstacles;
  std::vector<std::unique_ptr<ObstacleBase>> obstacles;
  // STUDENT CODE (end)

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void PlaceObstacles();  // STUDENT CODE
  void Update();
};

#endif