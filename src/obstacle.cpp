// STUDENT CODE: new class for fixed and moving obstacle

#include "obstacle.h"
#include "game.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <utility>

// ============================================================
// init static variables

int ObstacleBase::m_id_cnt = 0;
std::mutex ObstacleBase::m_mtx;

// ============================================================

void MovingObstacle::update()
{
  while (m_game->IsRunning()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(125));
    next();
  }
}

void MovingObstacle::next()
{
  std::lock_guard<std::mutex> lck(ObstacleBase::m_mtx);

  auto next_pos = next_position();
  if (m_game->IsObstacle(next_pos.first, next_pos.second)) {
    turn_around();
  }
  else {
    switch (m_direction) {
    case Direction::up:
      m_y -= m_speed;
      break;
    case Direction::down:
      m_y += m_speed;
      break;
    case Direction::left:
      m_x -= m_speed;
      break;
    case Direction::right:
      m_x += m_speed;
      break;
    }
  }
 
  m_x = fmod(m_x + m_grid_width, m_grid_width);
  m_y = fmod(m_y + m_grid_height, m_grid_height);
}

// ------------------------------------------------------------

std::pair<int, int> MovingObstacle::next_position() const
{
  int curr_x = static_cast<int>(m_x);
  int curr_y = static_cast<int>(m_y);
  switch (m_direction) {
  case Direction::up:
    return std::make_pair(curr_x, curr_y-1);
  case Direction::down:
    return std::make_pair(curr_x, curr_y+1);
  case Direction::left:
    return std::make_pair(curr_x-1, curr_y);
  case Direction::right:
    return std::make_pair(curr_x+1, curr_y);
  default:
    return std::make_pair(curr_x, curr_y);
  }
}

void MovingObstacle::turn_around()
{
  switch (m_direction) {
  case Direction::up:
    m_direction = Direction::down;
    break;
  case Direction::down:
    m_direction = Direction::up;
    break;
  case Direction::left:
    m_direction = Direction::right;
    break;
  case Direction::right:
    m_direction = Direction::left;
    break;
  }
}

// ============================================================
