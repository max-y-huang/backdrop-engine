#ifndef EVENT_LISTENER_HH
#define EVENT_LISTENER_HH

#include <functional>
#include <memory>

#include "Observer.hh"

using std::function;
using std::shared_ptr;

namespace Backdrop {

class EventListener {
  int id;
  function<void(shared_ptr<Observer::State>)> func;

 public:
  enum Type {
    _None,
    Tick,
  };
  static int idCounter;
  EventListener(int id, function<void(shared_ptr<Observer::State>)> func) : id{id}, func{func} {}
  bool matchesId(int _id);
  void run(shared_ptr<Observer::State> state);
};

}  // namespace Backdrop

#endif
