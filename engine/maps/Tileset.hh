#ifndef TILESET_HH
#define TILESET_HH

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace Backdrop {

class Tileset final {
 public:
  struct TileData {
    int layer;
    bool passable;
    bool bush;
  };

 private:
  string id;
  int width;
  int height;
  bool autoTiles;
  int animationFrames;
  vector<Tileset::TileData> tileData;
  void loadData(string id);

 public:
  Tileset(string id);
  string getId();
  int getWidth();
  int getHeight();
  bool isAutoTiles();
  int getAnimationFrames();
  vector<Tileset::TileData> getTileData();
};

}  // namespace Backdrop

#endif
