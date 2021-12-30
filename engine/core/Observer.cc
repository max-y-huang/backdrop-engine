#include "Observer.hh"

#include <memory>
#include <queue>
#include <utility>

using std::pair;
using std::priority_queue;
using std::shared_ptr;

namespace Backdrop {

void Observer::Subject::notifyObservers(shared_ptr<Observer::State> state) {
  auto _observers = observers;
  while (!_observers.empty()) {
    auto observer = _observers.top().second;
    observer->onNotify(state);
    _observers.pop();
  }
}

void Observer::Subject::notifyObservers() {
  notifyObservers(getState());
}

shared_ptr<Observer::State> Observer::Subject::getState() {
  return std::make_shared<Observer::State>();
}

void Observer::Subject::attach(shared_ptr<Observer> observer, int priority) {
  observers.push({priority, observer});
}

void Observer::Subject::detach(shared_ptr<Observer> observer) {
  priority_queue<pair<int, shared_ptr<Observer>>> _observers;
  while (!observers.empty()) {
    if (observers.top().second != observer) {
      _observers.push(observers.top());
    }
    observers.pop();
  }
  observers = _observers;
}

}  // namespace Backdrop
