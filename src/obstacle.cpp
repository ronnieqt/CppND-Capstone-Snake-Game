// STUDENT CODE: new class for fixed and moving obstacle

#include "obstacle.h"
#include "game.h"
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>

/* FIXME: todo list
 * pass in frame width and height
 * choose directions randomly after hitting another obstacle
 * randomly (for direction) initialize moving obstacles
 */

// ============================================================
// init static variables

int ObstacleBase::m_id_cnt = 0;
std::mutex ObstacleBase::m_mtx;

// ============================================================

int MovingObstacle::next_x() const
{
  int curr_x = static_cast<int>(m_x);
  switch (m_direction) {
  case Direction::up:
  case Direction::down:
    break;
  case Direction::left:
    curr_x -= 1; break;
  case Direction::right:
    curr_x += 1; break;
  }
  return curr_x;
}

int MovingObstacle::next_y() const
{
  int curr_y = static_cast<int>(m_y);
  switch (m_direction) {
  case Direction::up:
    curr_y -= 1; break;
  case Direction::down:
    curr_y += 1; break;
  case Direction::left:
  case Direction::right:
    break;
  }
  return curr_y;
}

void MovingObstacle::update()
{
  std::cout << "Thread: " << std::this_thread::get_id() << "\n";
  std::cout << "Obstacle(" << get_id() << "): " << get_x() << ", " << get_y() << "\n";
  while (m_game->IsRunning()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    next();
  }
}

void MovingObstacle::next()
{
  std::lock_guard<std::mutex> lck(ObstacleBase::m_mtx);

  switch (m_direction) {
  case Direction::up:
    if (m_game->IsObstacle(m_x, next_y())) {
      m_direction = Direction::down;
    }
    break;
  case Direction::down:
    if (m_game->IsObstacle(m_x, next_y())) {
      m_direction = Direction::up;
    }
    break;
  case Direction::left:
    if (m_game->IsObstacle(next_x(), m_y)) {
      m_direction = Direction::right;
    }
    break;
  case Direction::right:
    if (m_game->IsObstacle(next_x(), m_y)) {
      m_direction = Direction::left;
    }
    break;
  }

  switch (m_direction) {
  case Direction::up:
    m_y -= m_speed; break;
  case Direction::down:
    m_y += m_speed; break;
  case Direction::left:
    m_x -= m_speed; break;
  case Direction::right:
    m_x += m_speed; break;
  }
  // FIXME: improve
  m_x = fmod(m_x + 32, 32);
  m_y = fmod(m_y + 32, 32);
}

// ============================================================
