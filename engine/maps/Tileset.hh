#ifndef TILESET_HH
#define TILESET_HH

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../core/CollisionBox.hh"
#include "../enums.hh"

using std::string;
using std::vector;

namespace Backdrop {

class Tileset final {
 public:
  struct TileData {
    string spritesheetSrc;
    int layer;
    string autoTileType;
    bool animated;
    vector<CollisionBox::InitializerList> collisionBoxes;
    float offsetX;
    float offsetY;
  };

 private:
  vector<Tileset::TileData> tileData;
  void loadData();

 public:
  Tileset();
  vector<Tileset::TileData> getTileData();
};

}  // namespace Backdrop

#endif
