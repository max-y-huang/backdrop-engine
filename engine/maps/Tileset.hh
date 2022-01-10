#ifndef TILESET_HH
#define TILESET_HH

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "../core/CollisionBox.hh"

using std::string;
using std::vector;

namespace Backdrop {

class Tileset final {
 public:
  struct TileData {
    int layer;
    vector<CollisionBox::InitializerList> collisionBoxes;
  };

 private:
  string id;
  int width;
  int height;
  bool autoTiles;
  vector<Tileset::TileData> tileData;
  void loadData(string id);

 public:
  Tileset(string id);
  string getId();
  int getWidth();
  int getHeight();
  bool isAutoTiles();
  vector<Tileset::TileData> getTileData();
};

}  // namespace Backdrop

#endif
