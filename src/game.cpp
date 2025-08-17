#include "game.h"
#include <SDL_rect.h>
#include <algorithm>

Game::Game(std::size_t grid_width, std::size_t grid_height, int nb_obstacles)
  : snake(this, grid_width, grid_height)
  , nb_obstacles{nb_obstacles}
  , engine(dev())
  , random_w(0, static_cast<int>(grid_width - 1))
  , random_h(0, static_cast<int>(grid_height - 1))
{
  PlaceObstacles();
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

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
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is smaller than the target ms_per_frame),
    // delay the loop to achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
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
    x = random_w(engine);
    y = random_h(engine);
    obstacles.insert(SDL_Point{x, y});
  }
}

bool Game::ObstacleCell(int x, int y) const
{
  const auto it = std::find_if(
    obstacles.cbegin(), obstacles.cend(),
    [x,y](const SDL_Point& p){ return (x == p.x) && (y == p.y); });
  return it != obstacles.cend();
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
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
