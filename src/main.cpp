#include <iostream>
#include <memory>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr int nbObstacles{static_cast<int>(0.012*kGridWidth*kGridWidth)};  // STUDENT CODE

  auto game = std::make_shared<Game>(kGridWidth, kGridHeight, nbObstacles);
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  game->Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "User  : " << game->GetUsername() << "\n";
  std::cout << "Score : " << game->GetScore() << "\n";
  std::cout << "Size  : " << game->GetSize() << "\n";

  return 0;
}
