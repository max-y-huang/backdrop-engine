#ifndef OBJECT_HH
#define OBJECT_HH

#include <functional>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"

using std::function;
using std::shared_ptr;
using std::vector;

namespace Backdrop {

class Object : public Observer {
 public:
  struct Position {
    int x, y;
  };

 private:
  vector<EventListener> onTickFunctions;
  // Position position;
  void onNotify(shared_ptr<Observer::State> state);
  void runOnTickFunctions(shared_ptr<Clock::State> state);

 public:
  Position position;
  Object(Position position) : position{position} {}
  int addEventListener(EventListener::Type type, function<void(shared_ptr<Observer::State>)> func);
  void removeEventListener(int id);
};

}  // namespace Backdrop

#endif
