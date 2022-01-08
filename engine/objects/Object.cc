#include "Object.hh"

#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/CollisionBox.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"
#include "../core/Position.hh"
#include "../enums.h"

using std::function;
using std::shared_ptr;
using std::vector;

namespace Backdrop {

Object::Object(Position _position, vector<CollisionBox::InitializerList> _collisionBoxes) {
  for (auto params : _collisionBoxes) {
    auto temp = std::make_shared<CollisionBox>(position, params.x, params.y, params.width, params.height);
    collisionBoxes.push_back(temp);
  }
  spriteManager = std::make_shared<ObjectSpriteManager>();
  attach(spriteManager, 200);
  moveTo(_position);
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

bool Object::touching(shared_ptr<Object> other) {
  if (shared_from_this() == other) {
    return false;
  }
  for (auto a : collisionBoxes) {
    for (auto b : other->collisionBoxes) {
      if (a->touching(b)) {
        return true;
      }
    }
  }
  return false;
}

void Object::moveTo(Position _position) {
  position = _position;
  auto moveState = std::make_shared<Object::MoveState>(position.direction);
  notifyObservers(moveState);
}
void Object::moveTo(float x, float y, Direction direction) {
  moveTo({x / 48, y / 48, direction});
}
void Object::moveTo(float x, float y) {
  moveTo(x / 48, y / 48, position.direction);
}

}  // namespace Backdrop
