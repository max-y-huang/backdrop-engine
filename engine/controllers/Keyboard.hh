#ifndef KEYBOARD_HH
#define KEYBOARD_HH

#include <map>
#include <memory>
#include <string>

#include "../core/Observer.hh"
#include "../enums.hh"

using std::map;
using std::string;

namespace Backdrop {

// NOTE: Mouse buttons are stored as keyboard keys (with an offset of +100).

class Keyboard final : public Observer::Subject, public Observer {
  static shared_ptr<Keyboard> instance;

 public:
  struct State final : public Observer::State {
    string action;
    bool active;
    State(string action, bool active) : action{action}, active{active} {};
  };

 private:
  map<int, bool> keysPressed;
  map<int, string> actionBindings;
  void onNotify(shared_ptr<Observer::State> state);
  void createActionMap();
  void notifyActions();

 public:
  Keyboard();
  Keyboard(Keyboard &other) = delete;              // Disallow instances of this class.
  void operator=(const Keyboard &other) = delete;  // Disallow instances of this class.
  static shared_ptr<Keyboard> getInstance();
  void update();
};

}  // namespace Backdrop

#endif
