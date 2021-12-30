#include "Object.hh"

#include <functional>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"
#include "../enums.h"

using std::function;
using std::shared_ptr;
using std::weak_ptr;

namespace Backdrop {

Object::Object(Position position) : position{position} {
  fieldSpriteManager = std::make_shared<FieldSpriteManager>();
  attach(fieldSpriteManager, 200);
}

void Object::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  auto keyboardState = std::dynamic_pointer_cast<Keyboard::State>(state);
  if (clockState) {
    runOnTickFunctions(clockState);
  }
  if (keyboardState) {
    runOnActionKeyFunctions(keyboardState);
  }
}

void Object::runOnTickFunctions(shared_ptr<Clock::State> state) {
  for (auto listener : onTickFunctions) {
    listener.run(state);
  }
}

void Object::runOnActionKeyFunctions(shared_ptr<Keyboard::State> state) {
  for (auto listener : onActionKeyFunctions) {
    listener.run(state);
  }
}

int Object::onTick(function<void(shared_ptr<Clock::State>)> func) {
  onTickFunctions.push_back({func});
  return EventListenerCounter::counter;
}

int Object::onActionKey(function<void(shared_ptr<Keyboard::State>)> func) {
  onActionKeyFunctions.push_back({func});
  return EventListenerCounter::counter;
}

void Object::removeEventListener(int id) {
  // Remove from onTickFunctions.
  for (size_t i = 0; i < onTickFunctions.size(); ++i) {
    if (onTickFunctions[i].matchesId(id)) {
      onTickFunctions.erase(onTickFunctions.begin() + i);
      return;
    }
  }
  // Remove from onActionKeyFunctions.
  for (size_t i = 0; i < onActionKeyFunctions.size(); ++i) {
    if (onActionKeyFunctions[i].matchesId(id)) {
      onActionKeyFunctions.erase(onActionKeyFunctions.begin() + i);
      return;
    }
  }
}

float Object::Position::getX() {
  return x;
}
float Object::Position::getY() {
  return y;
}
Direction Object::Position::getDirection() {
  return direction;
}

void Object::moveUp() {
  position.y -= dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Up;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Up;
  notifyObservers(state);
}
void Object::moveDown() {
  position.y += dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Down;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Down;
  notifyObservers(state);
}
void Object::moveLeft() {
  position.x -= dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Left;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Left;
  notifyObservers(state);
}
void Object::moveRight() {
  position.x += dashing ? dashSpeed : walkSpeed;
  position.direction = Direction::Right;
  auto state = std::make_shared<Object::State>("move");
  state->direction = Direction::Right;
  notifyObservers(state);
}

void Object::setDash(bool _dashing) {
  dashing = _dashing;
}

}  // namespace Backdrop
