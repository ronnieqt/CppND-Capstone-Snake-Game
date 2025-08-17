// STUDENT CODE: utilities for SDL

#include <SDL.h>

// ============================================================
// Utils to compare 2 SDL_Points

inline bool operator==(const SDL_Point &p1, const SDL_Point &p2)
{
  return (p1.x == p2.x) & (p1.y == p2.y);
}

inline bool operator!=(const SDL_Point &p1, const SDL_Point &p2)
{
  return !(p1 == p2);
}

inline bool operator<(const SDL_Point &p1, const SDL_Point &p2)
{
  return (p1.x < p2.x) || (p1.x == p2.x && p1.y < p2.y);
}

// ============================================================
