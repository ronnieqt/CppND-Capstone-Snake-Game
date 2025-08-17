#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include <SDL.h>
#include "obstacle.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(const Snake snake, const std::vector<std::unique_ptr<ObstacleBase>>& obstacles, const SDL_Point& food);
  void UpdateWindowTitle(const std::string& user, int score, int fps);  // STUDENT CODE

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif
