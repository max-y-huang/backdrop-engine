#ifndef POSITION_HH
#define POSITION_HH

#include "../enums.h"

namespace Backdrop {

class Position {
  friend class Object;
  friend class Character;
  float x, y;
  Direction direction;

 public:
  Position() {}
  Position(float x, float y, Direction direction);
  Position(float x, float y);
  float getX();
  float getY();
  Direction getDirection();
  // void moveUp();
  // void moveDown();
  // void moveLeft();
  // void moveRight();
};

}  // namespace Backdrop

#endif