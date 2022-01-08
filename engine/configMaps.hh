#ifndef CONFIG_MAPS_HH
#define CONFIG_MAPS_HH

#include <map>
#include <string>

#include "enums.hh"

using std::map;
using std::string;

namespace Backdrop::ConfigMap {

class Action {
  static map<string, Backdrop::Action> enumMap;

 public:
  Action(Action &other) = delete;                // Disallow instances of this class.
  void operator=(const Action &other) = delete;  // Disallow instances of this class.
  static Backdrop::Action getAction(string code);
};

}  // namespace Backdrop::ConfigMap

#endif
