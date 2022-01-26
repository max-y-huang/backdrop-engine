#include "Tileset.hh"

#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/nlohmann/json.hpp"
#include "../configMaps.hh"
#include "../enums.hh"

using nlohmann::json;
using std::string;

namespace Backdrop {

Tileset::Tileset() {
  loadData();
}

void Tileset::loadData() {
  std::ifstream file{"config/tilesets.json"};
  json data;
  file >> data;
  for (auto tile : data.items()) {
    auto params = tile.value();
    string spritesheetSrc = string(params["spritesheetSrc"]);
    int layer = int(params["layer"]);
    AutoTileType autoTileType = ConfigMap::AutoTileType::getAutoTileType(string(params["autoTileType"]));
    bool animated = bool(params["animated"]);
    vector<CollisionBox::InitializerList> collisionBoxes;
    for (auto collisionBox : params["collisionBoxes"].items()) {
      auto params = collisionBox.value();
      collisionBoxes.push_back({float(params["x"]), float(params["y"]), float(params["width"]), float(params["height"])});
    }
    tileData.push_back({spritesheetSrc, layer, autoTileType, animated, collisionBoxes});
  }
}

vector<Tileset::TileData> Tileset::getTileData() {
  return tileData;
}

}  // namespace Backdrop
