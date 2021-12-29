#include "Object.hh"

#include <functional>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"

using std::function;
using std::shared_ptr;

namespace Backdrop {

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

void Object::Position::moveUp() {
  y -= 0.25;
}
void Object::Position::moveDown() {
  y += 0.25;
}
void Object::Position::moveLeft() {
  x -= 0.25;
}
void Object::Position::moveRight() {
  x += 0.25;
}

}  // namespace Backdrop
