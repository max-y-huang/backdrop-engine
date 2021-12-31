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
  string id;
  float walkSpeed = 4;
  float dashSpeed = 10;
  void moveInDirection(Direction direction);

 public:
  bool dashing = false;
  Character(Object::Position _position, string id);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void setDash(bool _dashing);
};

}  // namespace Backdrop

#endif
