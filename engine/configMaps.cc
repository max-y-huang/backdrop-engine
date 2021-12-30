#include "configMaps.hh"

#include <string>

#include "enums.h"

namespace Backdrop::ConfigMap {

map<string, Backdrop::Action> Action::enumMap{
    {"MoveUp", Backdrop::Action::MoveUp},
    {"MoveDown", Backdrop::Action::MoveDown},
    {"MoveLeft", Backdrop::Action::MoveLeft},
    {"MoveRight", Backdrop::Action::MoveRight},
    {"Dash", Backdrop::Action::Dash},
    {"Attack", Backdrop::Action::Attack},
};

Backdrop::Action Action::getAction(string code) {
  return enumMap.count(code) ? enumMap[code] : Backdrop::Action::_None;
}

}  // namespace Backdrop::ConfigMap
