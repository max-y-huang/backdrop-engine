#ifndef TILE_HH
#define TILE_HH

#include <memory>

#include "../managers/TileSpriteManager.hh"
#include "Tileset.hh"

using std::shared_ptr;

namespace Backdrop {

class Tile {
  int index;

 public:
  shared_ptr<TileSpriteManager> spriteManager;
  Tile(int index, Tileset::TileData tileData);
  int getIndex();
};

}  // namespace Backdrop

#endif
