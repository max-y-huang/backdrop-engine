#include "configMaps.hh"

#include <string>

#include "enums.hh"

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
  return enumMap.count(code) ? enumMap[code] : Backdrop::Action::NoAction;
}

map<string, Backdrop::AutoTileType> AutoTileType::enumMap{
    {"none", Backdrop::AutoTileType::NoAutoTile},
    {"normal", Backdrop::AutoTileType::Normal},
    {"wall", Backdrop::AutoTileType::Wall},
};

Backdrop::AutoTileType AutoTileType::getAutoTileType(string code) {
  return enumMap.count(code) ? enumMap[code] : Backdrop::AutoTileType::NoAutoTile;
}

}  // namespace Backdrop::ConfigMap
