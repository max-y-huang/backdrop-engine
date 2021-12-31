#include "Tile.hh"

#include "../managers/TileSpriteManager.hh"

namespace Backdrop {

Tile::Tile(Object::Position _position, Tileset tileset, int index) : tileset{tileset}, index{index} {
  spriteManager = std::make_shared<TileSpriteManager>("assets/images/tilesets/" + tileset.getId() + ".png", tileset, index);
  attach(spriteManager, 200);
  moveTo(_position);
}

}  // namespace Backdrop
