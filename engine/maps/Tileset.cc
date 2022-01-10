#include "Tileset.hh"

#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/nlohmann/json.hpp"

using nlohmann::json;
using std::string;

namespace Backdrop {

Tileset::Tileset(string id) : id{id} {
  loadData(id);
}

void Tileset::loadData(string name) {
  std::ifstream file{"config/tilesets.json"};
  json data;
  file >> data;
  width = data[name]["width"];
  height = data[name]["height"];
  autoTiles = data[name]["autoTiles"];
  for (auto itemData : data[name]["tileData"].items()) {
    Tileset::TileData data;
    data.layer = itemData.value()["layer"];
    for (auto params : itemData.value()["collisionBoxes"].items()) {
      data.collisionBoxes.push_back({float(params.value()["x"]), float(params.value()["y"]), float(params.value()["width"]), float(params.value()["height"])});
    }
    tileData.push_back(data);
  }
}

string Tileset::getId() {
  return id;
}
int Tileset::getWidth() {
  return width;
}
int Tileset::getHeight() {
  return height;
}
bool Tileset::isAutoTiles() {
  return autoTiles;
}

vector<Tileset::TileData> Tileset::getTileData() {
  return tileData;
}

}  // namespace Backdrop
