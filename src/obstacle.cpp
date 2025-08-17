// STUDENT CODE: new class for fixed and moving obstacle

#include "obstacle.h"
#include <mutex>

// ============================================================
// init static variables

int ObstacleBase::m_id_cnt = 0;
std::mutex ObstacleBase::m_mtx;

// ============================================================

