#include "Observer.hh"

#include <memory>
#include <queue>
#include <utility>

using std::pair;
using std::priority_queue;
using std::shared_ptr;

namespace PonchoEngine {

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

void Observer::Subject::attach(shared_ptr<Observer> observer, int priority) {
  observers.push({priority, observer});
}

}  // namespace PonchoEngine
