#include "Object.hh"

#include <functional>
#include <memory>
#include <vector>

#include "../Clock.hh"
#include "../EventListener.hh"
#include "../Observer.hh"

using std::function;
using std::shared_ptr;

namespace PonchoEngine {

void Object::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    runOnTickFunctions(clockState);
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

}  // namespace PonchoEngine
