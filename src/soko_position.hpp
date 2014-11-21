#ifndef _SOKO_POSITION_H_
#define _SOKO_POSITION_H_

#include "helpers.hpp"

namespace Sokoban {
  /** This class represents a position on a sokoban board. */
  class SokoPosition {
    public:
      SokoPosition();
      SokoPosition(int x, int y);
      SokoPosition(const Direction& direction);
      SokoPosition operator+(const SokoPosition& other);

      int x, y;
  };
}

#endif // _SOKO_POSITION_H_
