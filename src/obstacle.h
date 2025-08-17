// STUDENT CODE: new class for fixed and moving obstacle

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <mutex>

// ============================================================

enum class ObstacleType
{
  unknown,
  fixed,
  moving,
};

class ObstacleBase
{
public:
  ObstacleBase(int x, int y)
    : m_type{ObstacleType::unknown}
    , m_id{m_id_cnt++}
    , m_position{x, y}
  {}
  virtual ~ObstacleBase() = default;

  // getters
  ObstacleType get_type() const { return m_type; }
  int get_id() const { return m_id; }
  int get_x() const { return m_position.x; }
  int get_y() const { return m_position.y; }

  virtual void run() = 0;

protected:
  ObstacleType m_type;      // identifies the obstacle type
  int m_id;                 // each obstacle has its unique id
  SDL_Point m_position;     // position of the obstacle (x,y)
  static std::mutex m_mtx;  // mutex shared by all obstacles

private:
  static int m_id_cnt;  // global variable for counting obstacle ids
};

inline bool operator<(const ObstacleBase& o1, const ObstacleBase& o2)
{
  return (o1.get_x() < o2.get_x()) || (o1.get_x() == o2.get_x() && o1.get_y() < o2.get_y());
}

// ============================================================

class FixedObstacle : public ObstacleBase
{
public:
  FixedObstacle(int x, int y) : ObstacleBase(x, y) {}
  void run() override {}
};

// ============================================================

class MovingObstacle : public ObstacleBase
{
public:
  MovingObstacle(int x, int y) : ObstacleBase(x, y) {}
  void run() override {}
};

// ============================================================

#endif
