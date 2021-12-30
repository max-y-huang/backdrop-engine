#include "Character.hh"

#include <functional>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"
#include "../enums.h"
#include "../managers/CharacterSpriteManager.hh"
#include "Object.hh"

using std::function;
using std::shared_ptr;
using std::weak_ptr;

namespace Backdrop {

Character::Character(Object::Position _position) {
  position = _position;
  spriteManager = std::make_shared<CharacterSpriteManager>();
  attach(spriteManager, 200);
}

void Character::moveUp() {
  position.y -= dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Up;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Up;
  notifyObservers(state);
}
void Character::moveDown() {
  position.y += dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Down;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Down;
  notifyObservers(state);
}
void Character::moveLeft() {
  position.x -= dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Left;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Left;
  notifyObservers(state);
}
void Character::moveRight() {
  position.x += dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Right;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Right;
  notifyObservers(state);
}

void Character::setDash(bool _dashing) {
  dashing = _dashing;
}

}  // namespace Backdrop
