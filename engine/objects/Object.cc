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
    if (keyboardState->action == Keyboard::Action::MoveUp) {
      --position.y;
    }
    if (keyboardState->action == Keyboard::Action::MoveDown) {
      ++position.y;
    }
    if (keyboardState->action == Keyboard::Action::MoveLeft) {
      --position.x;
    }
    if (keyboardState->action == Keyboard::Action::MoveRight) {
      ++position.x;
    }
  }
}

void Object::runOnTickFunctions(shared_ptr<Clock::State> state) {
  for (auto listener : onTickFunctions) {
    listener.run(state);
  }
}

int Object::addEventListener(EventListener::Type type, function<void(shared_ptr<Observer::State>)> func) {
  int id = ++EventListener::idCounter;
  if (type == EventListener::Tick) {
    onTickFunctions.push_back({id, func});
  }
  return id;
}

void Object::removeEventListener(int id) {
  for (size_t i = 0; i < onTickFunctions.size(); i++) {
    if (onTickFunctions[i].matchesId(id)) {
      onTickFunctions.erase(onTickFunctions.begin() + i);
      return;
    }
  }
}

}  // namespace Backdrop
