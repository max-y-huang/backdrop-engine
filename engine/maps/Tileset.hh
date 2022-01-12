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
    AutoTileType autoTileType;
    bool animated;
    vector<CollisionBox::InitializerList> collisionBoxes;
  };

 private:
  string id;
  vector<Tileset::TileData> tileData;
  void loadData(string id);

 public:
  Tileset(string id);
  string getId();
  vector<Tileset::TileData> getTileData();
};

}  // namespace Backdrop

#endif
