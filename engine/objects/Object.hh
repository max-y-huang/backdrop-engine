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
#include "../core/Position.hh"
#include "../managers/ObjectSpriteManager.hh"

using std::function;
using std::shared_ptr;
using std::string;
using std::vector;

namespace Backdrop {

class Character;

class Object : public Observer, public Observer::Subject, public std::enable_shared_from_this<Object> {
 public:
  struct CollideState final : public Observer::State {
    shared_ptr<Object> self;
    Position prevPosition;
    CollideState(shared_ptr<Object> self, Position prevPosition) : self{self}, prevPosition{prevPosition} {};
  };
  struct MoveState final : public Observer::State {
    Direction direction;
    MoveState(Direction direction) : direction{direction} {};
  };

 private:
  vector<EventListener<Clock::State>> onTickFunctions;
  vector<EventListener<Keyboard::State>> onActionKeyFunctions;
  void onNotify(shared_ptr<Observer::State> state);
  void runOnTickFunctions(shared_ptr<Clock::State> state);
  void runOnActionKeyFunctions(shared_ptr<Keyboard::State> state);

 public:
  Position position;
  shared_ptr<ObjectSpriteManager> spriteManager;
  Object() {}
  Object(Position _position);
  // virtual ~Object() = default;
  int onTick(function<void(shared_ptr<Clock::State>)> func);
  int onActionKey(function<void(shared_ptr<Keyboard::State>)> func);
  void removeEventListener(int id);
  void moveTo(Position _position);
  void moveTo(float x, float y, Direction direction);
  void moveTo(float x, float y);
};

}  // namespace Backdrop

#endif
