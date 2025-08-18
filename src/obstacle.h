// STUDENT CODE: new class for fixed and moving obstacle

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <algorithm>
#include <random>
#include <memory>
#include <mutex>
#include <thread>
#include <utility>
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

  MovingObstacle(std::shared_ptr<Game> game, std::size_t grid_width, std::size_t grid_height, int x, int y)
    : ObstacleBase(x, y)
    , m_eng(m_dev())
    , m_rand(0, 3)
    , m_game{game}
    , m_grid_width{grid_width}
    , m_grid_height{grid_height}
    , m_direction{static_cast<Direction>(m_rand(m_eng))}
    , m_speed{0.125}
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
  // core functions
  void update();  // update moving obstacle position
  void next();    // next move of the obstacle
  // utils
  std::pair<int, int> next_position() const;  // position next to (m_x,m_y) following m_direction
  void turn_around();                         // flip direction (up<->down, left<->right)

private:
  std::random_device m_dev;
  std::mt19937 m_eng;
  std::uniform_int_distribution<int> m_rand;

  std::shared_ptr<Game> m_game;
  std::size_t m_grid_width;
  std::size_t m_grid_height;
  std::vector<std::thread> m_threads;
  Direction m_direction;
  float m_speed;
};

// ============================================================

#endif
