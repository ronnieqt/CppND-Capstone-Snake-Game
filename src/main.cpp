#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "scoreboard.h"

int main()
{
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  constexpr int nbObstacles{static_cast<int>(0.012*kGridWidth*kGridWidth)};

  Scoreboard scoreboard;  // STUDENT CODE
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;

  Game game(kGridWidth, kGridHeight, nbObstacles);
  game.Run(controller, renderer, kMsPerFrame);

  std::cout << "Game has terminated successfully!\n";
  std::cout << "User  : " << scoreboard.GetUsername() << "\n";
  std::cout << "Score : " << game.GetScore() << "\n";
  std::cout << "Size  : " << game.GetSize() << "\n";

  // STUDENT CODE (begin)
  scoreboard.UpdateScore(game.GetScore());
  scoreboard.WriteToTxt();
  // STUDENT CODE (end)

  return 0;
}
