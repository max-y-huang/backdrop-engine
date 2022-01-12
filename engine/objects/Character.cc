#include "Character.hh"

#include <fstream>
#include <string>

#include "../../lib/nlohmann/json.hpp"
#include "../core/CollisionBox.hh"
#include "../core/FrameRate.hh"
#include "../core/Position.hh"
#include "../enums.hh"
#include "../managers/CharacterSpriteManager.hh"
#include "Object.hh"

using nlohmann::json;
using std::string;

namespace Backdrop {

Character::Character(string id, Position _position) : id{id} {
  std::ifstream file{"config/characters.json"};
  json data;
  file >> data;
  for (auto item : data[id]["collisionBoxes"].items()) {
    auto params = item.value();
    auto temp = std::make_shared<CollisionBox>(position, float(params["x"]), float(params["y"]), float(params["width"]), float(params["height"]));
    collisionBoxes.push_back(temp);
  }
  spriteManager = std::make_shared<CharacterSpriteManager>(data[id]["spritesheetSrc"]);
  attach(spriteManager, 200);
  moveTo(_position);
}

void Character::moveInDirection(Direction direction, float speedMultiplier) {
  Position prevPosition = position;
  float speed = (dashing ? dashSpeed : walkSpeed) / FrameRate::getInstance()->getFrameRate() * 48 * speedMultiplier;
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

void Character::moveUp(float speedMultiplier) {
  moveInDirection(Direction::Up, speedMultiplier);
}
void Character::moveDown(float speedMultiplier) {
  moveInDirection(Direction::Down, speedMultiplier);
}
void Character::moveLeft(float speedMultiplier) {
  moveInDirection(Direction::Left, speedMultiplier);
}
void Character::moveRight(float speedMultiplier) {
  moveInDirection(Direction::Right, speedMultiplier);
}
void Character::moveUp() {
  moveUp(1);
}
void Character::moveDown() {
  moveDown(1);
}
void Character::moveLeft() {
  moveLeft(1);
}
void Character::moveRight() {
  moveRight(1);
}

void Character::setDash(bool _dashing) {
  dashing = _dashing;
}

}  // namespace Backdrop
