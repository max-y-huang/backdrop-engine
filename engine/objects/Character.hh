#ifndef CHARACTER_HH
#define CHARACTER_HH

#include <memory>

// #include "../managers/CharacterSpriteManager.hh"
#include "Object.hh"

using std::shared_ptr;

namespace Backdrop {

// class CharacterSpriteManager;

class Character : public Object {
  float walkSpeed = 1 / 16.0;
  float dashSpeed = 1 / 6.0;

 public:
  // shared_ptr<CharacterSpriteManager> fieldSpriteManager;
  bool dashing = false;
  Character(Object::Position _position);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void setDash(bool _dashing);
};

}  // namespace Backdrop

#endif
