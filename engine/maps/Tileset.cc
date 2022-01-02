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
  for (auto pair : data[name].items()) {
    if (pair.key() == "width") {
      width = pair.value();
    } else if (pair.key() == "height") {
      height = pair.value();
    } else if (pair.key() == "autoTiles") {
      autoTiles = pair.value();
    } else if (pair.key() == "animationFrames") {
      animationFrames = pair.value();
    }
    if (pair.key() == "tileData") {
      for (auto dataJson : pair.value()) {
        Tileset::TileData data;
        for (auto pair : dataJson.items()) {
          if (pair.key() == "layer") {
            data.layer = pair.value();
          } else if (pair.key() == "passable") {
            data.passable = pair.value();
          } else if (pair.key() == "bush") {
            data.bush = pair.value();
          }
        }
        tileData.push_back(data);
      }
    }
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
int Tileset::getAnimationFrames() {
  return animationFrames;
}

vector<Tileset::TileData> Tileset::getTileData() {
  return tileData;
}

}  // namespace Backdrop
