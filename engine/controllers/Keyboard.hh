#ifndef KEYBOARD_HH
#define KEYBOARD_HH

#include <map>
#include <memory>
#include <string>

#include "../core/Observer.hh"

using std::map;
using std::string;

namespace Backdrop {

class Keyboard final : public Observer::Subject, public Observer {
 public:
  enum Action {
    _None,
    MoveUp,
    MoveDown,
    MoveLeft,
    MoveRight,
  };
  struct State final : public Observer::State {
    Keyboard::Action action;
    State(Keyboard::Action action) : action{action} {};
  };

 private:
  map<string, bool> keysPressed;
  map<string, Keyboard::Action> actionMap;
  void onNotify(shared_ptr<Observer::State> state);
  shared_ptr<Observer::State> getState();
  void createActionMap();

 public:
  Keyboard();
  void update();
};

}  // namespace Backdrop

#endif
