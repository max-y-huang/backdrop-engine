#include "Map.hh"

namespace Backdrop {

Map::Map() {
  Map(20, 20);
}
Map::Map(int width, int height) : width{width}, height{height} {
  tiles.resize(height);
  for (int i = 0; i < height; ++i) {
    tiles[i].resize(width);
  }
}

int Map::getWidth() {
  return width;
}
int Map::getHeight() {
  return height;
}
shared_ptr<Tile> Map::getTile(int x, int y) {
  return tiles[y][x];
}

void Map::addTile(shared_ptr<Tile> tile) {
  tiles[tile->position.getY()][tile->position.getX()] = tile;
}

}  // namespace Backdrop
