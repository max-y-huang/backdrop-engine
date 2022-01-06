#include "Character.hh"

#include <string>

#include "../core/FrameRate.hh"
#include "../enums.h"
#include "../managers/CharacterSpriteManager.hh"
#include "Object.hh"

using std::string;

namespace Backdrop {

Character::Character(string id, Object::Position _position) : id{id} {
  spriteManager = std::make_shared<CharacterSpriteManager>("assets/images/characters/spritesheets/" + id + "_walk.png");
  attach(spriteManager, 200);
  moveTo(_position);
}

void Character::moveInDirection(Direction direction) {
  Position prevPosition = position;
  float speed = (dashing ? dashSpeed : walkSpeed) / FrameRate::getInstance()->getFrameRate() * 48;
  if (direction == Direction::Up) {
    position.y -= speed;
  } else if (direction == Direction::Down) {
    position.y += speed;
  } else if (direction == Direction::Left) {
    position.x -= speed;
  } else if (direction == Direction::Right) {
    position.x += speed;
  }
  position.direction = direction;
  moveTo(position);
  auto collideState = std::make_shared<Object::CollideState>(shared_from_this(), prevPosition);
  notifyObservers(collideState);
}

void Character::moveUp() {
  moveInDirection(Direction::Up);
}
void Character::moveDown() {
  moveInDirection(Direction::Down);
}
void Character::moveLeft() {
  moveInDirection(Direction::Left);
}
void Character::moveRight() {
  moveInDirection(Direction::Right);
}

void Character::setDash(bool _dashing) {
  dashing = _dashing;
}

}  // namespace Backdrop
