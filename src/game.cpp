#include "game.h"
#include "obstacle.h"
#include "scoreboard.h"
#include <SDL_rect.h>
#include <algorithm>
#include <memory>
#include <iostream>
#include <mutex>

Game::Game(std::size_t grid_width, std::size_t grid_height, int nb_obstacles)
  : snake(this, grid_width, grid_height)
  , scoreboard()  // STUDENT CODE
  , nb_obstacles{nb_obstacles}
  , engine_i(dev())
  , random_w(0, static_cast<int>(grid_width - 1))
  , random_h(0, static_cast<int>(grid_height - 1))
  , engine_f(dev())
  , random_f(0.0, 1.0)
{}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  PlaceObstacles();
  PlaceFood();

  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;

  // STUDENT CODE (begin)
  for (const auto &obst : obstacles) {
    obst->run();  // launch threads for moving obstacles
  }
  // STUDENT CODE (end)

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, obstacles, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(GetUsername(), score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is smaller than the target ms_per_frame),
    // delay the loop to achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

  scoreboard.UpdateScore(score);  // STUDENT CODE
}

void Game::PlaceFood()
{
  int x, y;
  while (true) {
    x = random_w(engine_i);
    y = random_h(engine_i);
    // Check that the location is not occupied by a snake/obstacle item before placing food.
    if (!ObstacleCell(x, y) && !snake.SnakeCell(x, y)) {  // STUDENT CODE
      food.x = x;
      food.y = y;
      return;
    }
  }
}

// STUDENT CODE (begin)
void Game::PlaceObstacles()
{
  int x{0}, y{0};
  for (int i = 0; i < nb_obstacles; ++i) {
    while (true) {
      x = random_w(engine_i);
      y = random_h(engine_i);
      if (!ObstacleCell(x, y)) {  // obstacles are placed before food and snake
        if (random_f(engine_f) < 0.2) {  // FIXME: make this param configurable
          obstacles.emplace_back(std::make_unique<MovingObstacle>(get_shared_this(), x, y));
        }
        else {
          obstacles.emplace_back(std::make_unique<FixedObstacle>(x, y));
        }
        break;
      }
    }
  }

  obstacles.emplace_back(std::make_unique<MovingObstacle>(get_shared_this(), 10, 8));
  // obstacles.emplace_back(std::make_unique<MovingObstacle>(get_shared_this(), 10, 9));
  for (const auto &o : obstacles) {
    std::cout << "Obstacle(" << o->get_id() << ") at "
              << "(" << o->get_x() << "," << o->get_y() << ")\n";
  }
}

bool Game::IsObstacle(int x, int y) const
{
  auto it = std::find_if(obstacles.cbegin(), obstacles.cend(),
                         [x,y](const auto& o){ return (x == o->get_x()) && (y == o->get_y()); });
  return it != obstacles.cend();
}

bool Game::ObstacleCell(int x, int y)
{
  std::lock_guard<std::mutex> lck(ObstacleBase::m_mtx);
  return IsObstacle(x, y);
}
// STUDENT CODE (end)

void Game::Update()
{
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
    snake.speed += 0.01;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
bool Game::IsRunning() const { return running && snake.alive; }
std::string Game::GetUsername() const { return scoreboard.GetUsername(); }
