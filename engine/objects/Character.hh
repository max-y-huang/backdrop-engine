#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <memory>
#include <string>

#include "../core/CollisionBox.hh"
#include "../core/Position.hh"
#include "../enums.hh"
#include "Object.hh"

using std::shared_ptr;
using std::string;

namespace Backdrop {

class Character : public Object {
  string id;
  float walkSpeed = 3;
  float dashSpeed = 7;
  void moveInDirection(Direction direction, float speedMultiplier);

 public:
  bool dashing = false;
  Character(string id, Position _position);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void moveUp(float speedMultiplier);
  void moveDown(float speedMultiplier);
  void moveLeft(float speedMultiplier);
  void moveRight(float speedMultiplier);
  void setDash(bool _dashing);
};

}  // namespace Backdrop

#endif
