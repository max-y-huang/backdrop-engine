#include "Map.hh"

#include "../enums.h"
#include "../managers/TileSpriteManager.hh"
#include "Tileset.hh"

namespace Backdrop {

Map::Map(Tileset tileset, int width, int height) : tileset{tileset}, width{width}, height{height} {
  tiles.resize(height);
  for (int i = 0; i < height; ++i) {
    tiles[i].resize(width);
  }
}

Map::Tile::Tile(Tileset tileset, int index) : tileset{tileset}, index{index} {
  spriteManager = std::make_shared<TileSpriteManager>(index, tileset.isAutoTiles(), tileset.getWidth(), "assets/images/tilesets/" + tileset.getId() + ".png");
}

Tileset Map::getTileset() {
  return tileset;
}
int Map::getWidth() {
  return width;
}
int Map::getHeight() {
  return height;
}
shared_ptr<Map::Tile> Map::getTile(int x, int y) {
  return tiles[y][x];
}

void Map::addTile(int index, int x, int y) {
  tiles[y][x] = std::make_shared<Map::Tile>(tileset, index);
}

}  // namespace Backdrop
