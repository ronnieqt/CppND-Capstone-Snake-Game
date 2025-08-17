// STUDENT CODE: new class for fixed and moving obstacle

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <algorithm>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

// ============================================================

class ObstacleBase
{
public:
  ObstacleBase(int x, int y)
    : m_id{m_id_cnt++}
    , m_x{static_cast<float>(x)}
    , m_y{static_cast<float>(y)}
  {}
  virtual ~ObstacleBase() = default;

  // getters
  int get_id() const { return m_id; }
  int get_x() const { return static_cast<int>(m_x); }
  int get_y() const { return static_cast<int>(m_y); }

  virtual void run() = 0;

public:
  static std::mutex m_mtx;  // mutex shared by all obstacles

protected:
  int m_id;             // each obstacle has its unique id
  float m_x;            // position.x of the obstacle
  float m_y;            // position.y of the obstacle

private:
  static int m_id_cnt;  // global variable for counting obstacle ids
};

// ============================================================

class FixedObstacle : public ObstacleBase
{
public:
  FixedObstacle(int x, int y) : ObstacleBase(x, y) {}
  void run() override {}
};

// ============================================================

class Game;

class MovingObstacle : public ObstacleBase
{
public:
  enum class Direction { up, down, left, right };

  MovingObstacle(std::shared_ptr<Game> game, int x, int y)
    : ObstacleBase(x, y)
    , m_game{game}
    , m_direction{Direction::right}  // TODO: randomize initial direction
    , m_speed{0.1}
  {}
  ~MovingObstacle()
  {
    std::for_each(m_threads.begin(), m_threads.end(), [](std::thread& t){ t.join(); });
  }

  void run() override
  {
    m_threads.emplace_back(std::thread(&MovingObstacle::update, this));
  }

private:
  void update();       // update moving obstacle position
  void next();         // next move of the obstacle
  int next_x() const;  // next position.x following m_direction
  int next_y() const;  // next position.y following m_direction
  // TODO: choose direction is a smart way

private:
  std::shared_ptr<Game> m_game;
  std::vector<std::thread> m_threads;
  Direction m_direction;
  float m_speed;
};

// ============================================================

#endif
