#include "configMaps.hh"

#include <string>

namespace Backdrop::ConfigMap {

map<string, Keyboard::Action> KeyboardAction::bindings{
    {"MoveUp", Keyboard::Action::MoveUp},
    {"MoveDown", Keyboard::Action::MoveDown},
    {"MoveLeft", Keyboard::Action::MoveLeft},
    {"MoveRight", Keyboard::Action::MoveRight},
};

Keyboard::Action KeyboardAction::getAction(string code) {
  return bindings.count(code) ? bindings[code] : Keyboard::Action::_None;
}

}  // namespace Backdrop::ConfigMap
