#include "Map.hh"

#include "../../lib/nlohmann/json.hpp"
#include "../Game.hh"
#include "../controllers/Clock.hh"
#include "../core/CollisionBox.hh"
#include "../core/Position.hh"
#include "../enums.hh"
#include "../managers/MapSpriteManager.hh"
#include "../managers/TileSpriteManager.hh"
#include "../objects/Object.hh"
#include "Tile.hh"
#include "Tileset.hh"

using nlohmann::json;

namespace Backdrop {

Map::Map(Game &game, Tileset tileset, json mapData) : game{game}, tileset{tileset}, width{mapData["width"]}, height{mapData["height"]} {
  for (auto tile : mapData["tiles"].items()) {
    tileData.push_back(tile.value());
  }
  spriteManager = std::make_shared<MapSpriteManager>(tiles);
  Clock::getInstance()->attach(spriteManager, 200);
  tiles.resize(height);
  for (int y = 0; y < height; ++y) {
    tiles[y].resize(width);
    for (int x = 0; x < width; ++x) {
      tiles[y][x].resize(3);
    }
  }
}

void Map::loadTiles() {
  for (auto tile : tileData) {
    addTile(tile["index"], tile["x"], tile["y"], false);
  }
  spriteManager->updateSprite();
}

int Map::getWidth() {
  return width;
}
int Map::getHeight() {
  return height;
}
shared_ptr<Tile> Map::getTile(int x, int y, int layer) {
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

void Map::addTile(int index, int x, int y, bool updateImage) {
  Tileset::TileData data = tileset.getTileData()[index];
  if (x >= 0 && x <= width - 1 && y >= 0 && y <= height - 1) {
    auto tile = std::make_shared<Tile>(index, data);
    int layer = data.layer;
    if (data.collisionBoxes.size() > 0) {
      auto object = std::make_shared<Object>(Position{float(x), float(y)}, data.collisionBoxes);
      object->setVisible(false);
      game.addObject(object);
    }
    tiles[y][x][layer] = tile;
    updateTileSpriteManagers(x, y, layer);
    if (updateImage) {
      spriteManager->updateSprite();
    }
  }
}
void Map::addTile(int index, int x, int y) {
  addTile(index, x, y, true);
}

}  // namespace Backdrop
