#include "Tile.hh"

namespace Backdrop {

Tile::Tile(Tileset tileset, int index) : tileset{tileset}, index{index} {
  spriteManager = std::make_shared<TileSpriteManager>(index, tileset.isAutoTiles(), tileset.getWidth(), "assets/images/tilesets/" + tileset.getId() + ".png");
}

int Tile::getIndex() {
  return index;
}

}  // namespace Backdrop
