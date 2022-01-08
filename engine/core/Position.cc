#include "Position.hh"

#include "../enums.hh"

namespace Backdrop {

Position::Position(float x, float y, Direction direction) : x{48 * x}, y{48 * y}, direction{direction} {}
Position::Position(float x, float y) : x{48 * x}, y{48 * y}, direction{Direction::Down} {}

float Position::getX() {
  return x;
}
float Position::getY() {
  return y;
}
Direction Position::getDirection() {
  return direction;
}

}  // namespace Backdrop
