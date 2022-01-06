#include "Object.hh"

#include <functional>
#include <memory>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"
#include "../enums.h"

using std::function;
using std::shared_ptr;

namespace Backdrop {

Object::Object(Position _position) {
  spriteManager = std::make_shared<ObjectSpriteManager>();
  attach(spriteManager, 200);
  moveTo(_position);
}

Object::Position::Position(float x, float y, Direction direction) : x{x}, y{y}, direction{direction} {}
Object::Position::Position(float x, float y) : x{x}, y{y}, direction{Direction::Down} {}

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

void Object::moveTo(Position _position) {
  position = _position;
  auto moveState = std::make_shared<Object::MoveState>(position.direction);
  notifyObservers(moveState);
}
void Object::moveTo(float x, float y, Direction direction) {
  moveTo({x, y, direction});
}
void Object::moveTo(float x, float y) {
  moveTo(x, y, position.direction);
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

}  // namespace Backdrop
