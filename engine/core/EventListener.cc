#include "EventListener.hh"

#include <functional>
#include <iostream>
#include <memory>

#include "Observer.hh"

using std::function;
using std::shared_ptr;

namespace PonchoEngine {

int EventListener::idCounter = 0;

bool EventListener::matchesId(int _id) {
  return id == _id;
}

void EventListener::run(shared_ptr<Observer::State> state) {
  func(state);
}

}  // namespace PonchoEngine
