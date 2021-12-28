#ifndef EVENT_LISTENER_HH
#define EVENT_LISTENER_HH

#include <functional>
#include <memory>

#include "Observer.hh"

using std::function;
using std::shared_ptr;

namespace Backdrop {

template <typename State>
class EventListener {
  function<void(shared_ptr<State>)> func;

 public:
  EventListener(function<void(shared_ptr<State>)> func) : func{func} {}
  void run(shared_ptr<State> state) { func(state); };
};

}  // namespace Backdrop

#endif
