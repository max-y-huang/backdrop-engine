#ifndef MAP_HH
#define MAP_HH

#include <map>
#include <memory>
#include <vector>

#include "../objects/Object.hh"
#include "../objects/Tile.hh"

using std::map;
using std::shared_ptr;
using std::vector;

namespace Backdrop {

class Map final {
  int width;
  int height;
  vector<vector<shared_ptr<Tile>>> tiles;

 public:
  Map();
  Map(int width, int height);
  int getWidth();
  int getHeight();
  shared_ptr<Tile> getTile(int x, int y);
  void addTile(shared_ptr<Tile> tile);
};

}  // namespace Backdrop

#endif
