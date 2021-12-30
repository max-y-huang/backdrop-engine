#ifndef EVENT_LISTENER_HH
#define EVENT_LISTENER_HH

#include <functional>
#include <memory>

#include "Observer.hh"

using std::function;
using std::shared_ptr;

namespace Backdrop {

struct EventListenerCounter {
  static int counter;
};

template <typename State>
class EventListener final {
  int id;
  function<void(shared_ptr<State>)> func;

 public:
  EventListener(function<void(shared_ptr<State>)> func) : func{func} {
    id = ++EventListenerCounter::counter;
  }
  void run(shared_ptr<State> state) { func(state); };
  bool matchesId(int _id) { return id == _id; }
};

}  // namespace Backdrop

#endif
