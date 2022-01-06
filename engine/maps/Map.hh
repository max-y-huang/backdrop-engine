#ifndef MAP_HH
#define MAP_HH

#include <memory>
#include <vector>

#include "../managers/MapSpriteManager.hh"
#include "../managers/TileSpriteManager.hh"
#include "Tile.hh"
#include "Tileset.hh"

using std::shared_ptr;
using std::vector;

namespace Backdrop {

class Game;

class Map final {
  Game &game;
  Tileset tileset;
  int width;
  int height;
  vector<vector<vector<shared_ptr<Tile>>>> tiles;
  void updateTileSpriteManagers(int x, int y, int layer);
  void updateTileSpriteManagers_helper(int layer, int x1, int y1, Direction d1, int x2, int y2, Direction d2);

 public:
  shared_ptr<MapSpriteManager> spriteManager;
  Map(Game &game, Tileset tileset, int width, int height);
  int getWidth();
  int getHeight();
  shared_ptr<Tile> getTile(int x, int y, int layer);
  void addTile(int index, int x, int y);
};

}  // namespace Backdrop

#endif
