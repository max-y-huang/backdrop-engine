#include "Tile.hh"

#include "../managers/TileSpriteManager.hh"
#include "Tileset.hh"

namespace Backdrop {

Tile::Tile(int index, Tileset::TileData tileData) : index{index} {
  spriteManager = std::make_shared<TileSpriteManager>(tileData.spritesheetSrc, tileData.type, tileData.animated, tileData.offsetX, tileData.offsetY);
}

int Tile::getIndex() {
  return index;
}

}  // namespace Backdrop
