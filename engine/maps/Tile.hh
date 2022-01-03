#ifndef TILE_HH
#define TILE_HH

#include <memory>

#include "../managers/TileSpriteManager.hh"
#include "Tileset.hh"

using std::shared_ptr;

namespace Backdrop {

class Tile {
  Tileset tileset;
  int index;

 public:
  shared_ptr<TileSpriteManager> spriteManager;
  Tile(Tileset tileset, int index);
  int getIndex();
};

}  // namespace Backdrop

#endif
