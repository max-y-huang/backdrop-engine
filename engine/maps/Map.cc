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

int Map::Tile::getIndex() {
  return index;
}

int Map::getWidth() {
  return width;
}
int Map::getHeight() {
  return height;
}
shared_ptr<Map::Tile> Map::getTile(int x, int y) {
  if (x < 0 || x >= width) {
    return nullptr;
  }
  if (y < 0 || y >= height) {
    return nullptr;
  }
  return tiles[y][x];
}

void Map::addTileHelper(int x1, int y1, Direction d1, int x2, int y2, Direction d2) {
  if (!getTile(x1, y1) || !getTile(x2, y2)) {
    return;
  }
  auto sameTile = (getTile(x1, y1)->getIndex() == getTile(x2, y2)->getIndex());
  getTile(x1, y1)->spriteManager->updateSameTileMap(d1, sameTile);
  getTile(x2, y2)->spriteManager->updateSameTileMap(d2, sameTile);
}

void Map::addTile(int index, int x, int y) {
  tiles[y][x] = std::make_shared<Map::Tile>(tileset, index);
  addTileHelper(x, y, Direction::Up, x, y - 1, Direction::Down);
  addTileHelper(x, y, Direction::Down, x, y + 1, Direction::Up);
  addTileHelper(x, y, Direction::Left, x - 1, y, Direction::Right);
  addTileHelper(x, y, Direction::Right, x + 1, y, Direction::Left);
  addTileHelper(x, y, Direction::UpLeft, x - 1, y - 1, Direction::DownRight);
  addTileHelper(x, y, Direction::UpRight, x + 1, y - 1, Direction::DownLeft);
  addTileHelper(x, y, Direction::DownLeft, x - 1, y + 1, Direction::UpRight);
  addTileHelper(x, y, Direction::DownRight, x + 1, y + 1, Direction::UpLeft);
}

}  // namespace Backdrop
