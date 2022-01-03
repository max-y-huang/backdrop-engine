#include "Map.hh"

#include "../enums.h"
#include "../managers/MapSpriteManager.hh"
#include "../managers/TileSpriteManager.hh"
#include "Tileset.hh"

namespace Backdrop {

Map::Map(Tileset tileset, int width, int height) : tileset{tileset}, width{width}, height{height} {
  spriteManager = std::make_shared<MapSpriteManager>(width, height);
  tiles.resize(height);
  for (int y = 0; y < height; ++y) {
    tiles[y].resize(width);
    for (int x = 0; x < width; ++x) {
      tiles[y][x].resize(3);
    }
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
shared_ptr<Map::Tile> Map::getTile(int x, int y, int layer) {
  if (x < 0 || x >= width) {
    return nullptr;
  }
  if (y < 0 || y >= height) {
    return nullptr;
  }
  return tiles[y][x][layer];
}

void Map::updateTileSpriteManagers_helper(int layer, int x1, int y1, Direction d1, int x2, int y2, Direction d2) {
  if (!getTile(x1, y1, layer) || !getTile(x2, y2, layer)) {
    return;
  }
  auto sameTile = (getTile(x1, y1, layer)->getIndex() == getTile(x2, y2, layer)->getIndex());
  getTile(x1, y1, layer)->spriteManager->updateSameTileMap(d1, sameTile);
  getTile(x2, y2, layer)->spriteManager->updateSameTileMap(d2, sameTile);
}

void Map::updateTileSpriteManagers(int x, int y, int layer) {
  updateTileSpriteManagers_helper(layer, x, y, Direction::Up, x, y - 1, Direction::Down);
  updateTileSpriteManagers_helper(layer, x, y, Direction::Down, x, y + 1, Direction::Up);
  updateTileSpriteManagers_helper(layer, x, y, Direction::Left, x - 1, y, Direction::Right);
  updateTileSpriteManagers_helper(layer, x, y, Direction::Right, x + 1, y, Direction::Left);
  updateTileSpriteManagers_helper(layer, x, y, Direction::UpLeft, x - 1, y - 1, Direction::DownRight);
  updateTileSpriteManagers_helper(layer, x, y, Direction::UpRight, x + 1, y - 1, Direction::DownLeft);
  updateTileSpriteManagers_helper(layer, x, y, Direction::DownLeft, x - 1, y + 1, Direction::UpRight);
  updateTileSpriteManagers_helper(layer, x, y, Direction::DownRight, x + 1, y + 1, Direction::UpLeft);
}

void Map::addTile(int index, int x, int y) {
  auto tile = std::make_shared<Map::Tile>(tileset, index);
  int layer = tileset.getTileData()[index].layer;
  tiles[y][x][layer] = tile;
  updateTileSpriteManagers(x, y, layer);
  spriteManager->setTileSpriteManager(tile->spriteManager, x, y, layer);
}

}  // namespace Backdrop
