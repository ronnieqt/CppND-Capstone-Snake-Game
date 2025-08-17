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

class Game : public std::enable_shared_from_this<Game>
{
public:
  Game(std::size_t grid_width, std::size_t grid_height, int nb_obstacles);
  ~Game() = default;  // FIXME: why we cannot see ~Game() called in main thread?

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);

  int GetScore() const;
  int GetSize() const;

  // STUDENT CODE (begin)
  std::string GetUsername() const;
  bool IsRunning() const;  // check if (the game is running) and (the snake is alive)

  std::shared_ptr<Game> get_shared_this() { return shared_from_this(); }

  bool IsObstacle(int x, int y) const;  // check (x,y) is an obstacle or not
  bool ObstacleCell(int x, int y);      // IsObstacle + mutex lock

  void WriteScore() { scoreboard.WriteToTxt(); };
  // STUDENT CODE (end)

private:
  Snake snake;
  SDL_Point food;
  // STUDENT CODE (begin)
  Scoreboard scoreboard;
  int nb_obstacles;
  std::vector<std::unique_ptr<ObstacleBase>> obstacles;
  // STUDENT CODE (end)

  std::random_device dev;
  std::mt19937 engine_i;  // for obstacle grids generation
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::mt19937 engine_f;  // for fixed/moving obstacle classification
  std::uniform_real_distribution<float> random_f;

  bool running{false};
  int score{0};

  void PlaceFood();
  void PlaceObstacles();  // STUDENT CODE
  void Update();
};

#endif