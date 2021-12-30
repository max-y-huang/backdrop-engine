#include "configMaps.hh"

#include <string>

namespace Backdrop::ConfigMap {

map<string, Keyboard::Action> KeyboardAction::enumMap{
    {"MoveUp", Keyboard::Action::MoveUp},
    {"MoveDown", Keyboard::Action::MoveDown},
    {"MoveLeft", Keyboard::Action::MoveLeft},
    {"MoveRight", Keyboard::Action::MoveRight},
    {"Dash", Keyboard::Action::Dash},
    {"Attack", Keyboard::Action::Attack},
};

Keyboard::Action KeyboardAction::getAction(string code) {
  return enumMap.count(code) ? enumMap[code] : Keyboard::Action::_None;
}

}  // namespace Backdrop::ConfigMap
