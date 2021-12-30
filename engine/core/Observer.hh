#ifndef OBSERVER_HH
#define OBSERVER_HH

#include <memory>
#include <queue>
#include <utility>

using std::pair;
using std::priority_queue;
using std::shared_ptr;

namespace Backdrop {

class Observer {
 public:
  struct State {
    virtual ~State() = default;
  };
  class Subject {
    priority_queue<pair<int, shared_ptr<Observer>>> observers;

   protected:
    virtual ~Subject() = default;
    void notifyObservers(shared_ptr<Observer::State> state);
    void notifyObservers();
    virtual shared_ptr<Observer::State> getState();

   public:
    void attach(shared_ptr<Observer> observer, int priority);
    void detach(shared_ptr<Observer> observer);
  };

 protected:
  virtual ~Observer() = default;
  virtual void onNotify(shared_ptr<Observer::State> state) = 0;
};

}  // namespace Backdrop

#endif
