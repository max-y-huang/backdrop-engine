#ifndef MAPS_HH
#define MAPS_hh

#include <map>
#include <string>

#include "../controllers/Keyboard.hh"

using std::map;
using std::string;

namespace Backdrop::ConfigMap {

class KeyboardAction {
  static map<string, Keyboard::Action> bindings;

 public:
  KeyboardAction(KeyboardAction &other) = delete;        // Disallow instances of this class.
  void operator=(const KeyboardAction &other) = delete;  // Disallow instances of this class.
  static Keyboard::Action getAction(string code);
};

}  // namespace Backdrop::ConfigMap

#endif
