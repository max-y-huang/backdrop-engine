#include "Tileset.hh"

#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/nlohmann/json.hpp"
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
    string type = string(params["type"]);
    bool animated = bool(params["animated"]);
    vector<CollisionBox::InitializerList> collisionBoxes;
    for (auto collisionBox : params["collisionBoxes"].items()) {
      auto params = collisionBox.value();
      collisionBoxes.push_back({float(params["x"]), float(params["y"]), float(params["width"]), float(params["height"])});
    }
    float offsetX = float(params["offset"]["x"]);
    float offsetY = float(params["offset"]["y"]);
    tileData.push_back({spritesheetSrc, layer, type, animated, collisionBoxes, offsetX, offsetY});
  }
}

vector<Tileset::TileData> Tileset::getTileData() {
  return tileData;
}

}  // namespace Backdrop
