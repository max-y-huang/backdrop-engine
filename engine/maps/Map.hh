#ifndef MAP_HH
#define MAP_HH

#include <memory>
#include <vector>

#include "../managers/TileSpriteManager.hh"
#include "Tileset.hh"

using std::shared_ptr;
using std::vector;

namespace Backdrop {

class Map final {
 public:
  class Tile {
    Tileset tileset;
    int index;

   public:
    shared_ptr<TileSpriteManager> spriteManager;
    Tile(Tileset tileset, int index);
    int getIndex();
  };

 private:
  Tileset tileset;
  int width;
  int height;
  vector<vector<shared_ptr<Map::Tile>>> tiles;
  void addTileHelper(int x1, int y1, Direction d1, int x2, int y2, Direction d2);

 public:
  Map(Tileset tileset, int width, int height);
  int getWidth();
  int getHeight();
  shared_ptr<Map::Tile> getTile(int x, int y);
  void addTile(int index, int x, int y);
};

}  // namespace Backdrop

#endif
