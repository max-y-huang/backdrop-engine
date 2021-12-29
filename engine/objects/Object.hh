#ifndef OBJECT_HH
#define OBJECT_HH

#include <functional>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"

using std::function;
using std::shared_ptr;
using std::vector;

namespace Backdrop {

class Object : public Observer {
 public:
  class Position {
    float x, y;

   public:
    Position(float x, float y) : x{x}, y{y} {}
    float getX();
    float getY();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
  };

 private:
  vector<EventListener<Clock::State>> onTickFunctions;
  vector<EventListener<Keyboard::State>> onActionKeyFunctions;
  void onNotify(shared_ptr<Observer::State> state);
  void runOnTickFunctions(shared_ptr<Clock::State> state);
  void runOnActionKeyFunctions(shared_ptr<Keyboard::State> state);

 public:
  Position position;
  Object(Position position) : position{position} {}
  int onTick(function<void(shared_ptr<Clock::State>)> func);
  int onActionKey(function<void(shared_ptr<Keyboard::State>)> func);
  void removeEventListener(int id);
};

}  // namespace Backdrop

#endif
