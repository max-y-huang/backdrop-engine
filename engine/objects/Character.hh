#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <memory>
#include <string>

#include "../enums.h"
#include "Object.hh"

using std::shared_ptr;
using std::string;

namespace Backdrop {

class Character : public Object {
  float walkSpeed = 1 / 16.0;
  float dashSpeed = 1 / 6.0;

 public:
  bool dashing = false;
  Character(Object::Position _position, string spritesheetSrc);
  void moveTo(Position _position);
  void moveTo(float x, float y, Direction direction);
  void moveTo(float x, float y);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void setDash(bool _dashing);
};

}  // namespace Backdrop

#endif
