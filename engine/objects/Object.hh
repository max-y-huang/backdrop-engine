#ifndef OBJECT_HH
#define OBJECT_HH

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "../controllers/Clock.hh"
#include "../controllers/Keyboard.hh"
#include "../core/EventListener.hh"
#include "../core/Observer.hh"
#include "../managers/FieldSpriteManager.hh"

using std::function;
using std::shared_ptr;
using std::string;
using std::vector;

namespace Backdrop {

class FieldSpriteManager;

class Object : public Observer, public Observer::Subject, public std::enable_shared_from_this<Object> {
 public:
  class Position {
    friend class Object;
    float x, y;
    Direction direction;

   public:
    Position(float x, float y, Direction direction) : x{x}, y{y}, direction{direction} {}
    float getX();
    float getY();
    Direction getDirection();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
  };
  struct State final : public Observer::State {
    string type;
    Direction direction;
    State(string type) : type{type} {};
  };

 private:
  vector<EventListener<Clock::State>> onTickFunctions;
  vector<EventListener<Keyboard::State>> onActionKeyFunctions;
  void onNotify(shared_ptr<Observer::State> state);
  void runOnTickFunctions(shared_ptr<Clock::State> state);
  void runOnActionKeyFunctions(shared_ptr<Keyboard::State> state);

 public:
  Position position;
  shared_ptr<FieldSpriteManager> fieldSpriteManager;
  bool walking = false;
  Object(Position position);
  int onTick(function<void(shared_ptr<Clock::State>)> func);
  int onActionKey(function<void(shared_ptr<Keyboard::State>)> func);
  void removeEventListener(int id);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
};

}  // namespace Backdrop

#endif
