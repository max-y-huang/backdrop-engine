#ifndef CONFIG_MAPS_HH
#define CONFIG_MAPS_HH

#include <map>
#include <string>

#include "controllers/Keyboard.hh"

using std::map;
using std::string;

namespace Backdrop::ConfigMap {

class KeyboardAction {
  static map<string, Keyboard::Action> enumMap;

 public:
  KeyboardAction(KeyboardAction &other) = delete;        // Disallow instances of this class.
  void operator=(const KeyboardAction &other) = delete;  // Disallow instances of this class.
  static Keyboard::Action getAction(string code);
};

}  // namespace Backdrop::ConfigMap

#endif
