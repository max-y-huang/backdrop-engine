#ifndef KEYBOARD_HH
#define KEYBOARD_HH

#include <SFML/Window/Keyboard.hpp>
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
    Dash,
    Attack,
  };
  struct State final : public Observer::State {
    Keyboard::Action action;
    bool active;
    State(Keyboard::Action action, bool active) : action{action}, active{active} {};
  };

 private:
  map<sf::Keyboard::Key, bool> keysPressed;
  map<sf::Keyboard::Key, Keyboard::Action> actionBindings;
  void onNotify(shared_ptr<Observer::State> state);
  void createActionMap();
  void notifyActions();

 public:
  Keyboard();
  void update();
};

}  // namespace Backdrop

#endif
