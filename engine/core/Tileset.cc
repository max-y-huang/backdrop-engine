#include "Tileset.hh"

#include <fstream>
#include <iostream>
#include <string>

#include "../../lib/nlohmann/json.hpp"

using nlohmann::json;
using std::string;

namespace Backdrop {

Tileset::Tileset(string id) : id{id} {
  initializeParameters(id);
  texture.loadFromFile("assets/images/tilesets/" + id + ".png");
}

void Tileset::initializeParameters(string name) {
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
  }

  // std::cout << "dimensions: " << width << "x" << height << std::endl;
  // std::cout << "auto-tiles: " << (autoTiles ? "true" : "false") << std::endl;
  // std::cout << "animation frames: " << animationFrames << std::endl;
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

}  // namespace Backdrop
