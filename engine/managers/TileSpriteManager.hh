#ifndef TILE_SPRITE_MANAGER_HH
#define TILE_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../../lib/nlohmann/json.hpp"
#include "../enums.hh"

using nlohmann::json;
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;

namespace Backdrop {

class TileSpriteManager final {
  sf::Image spritesheetImage;
  vector<sf::Image> images;
  int index;
  AutoTileType autoTileType;
  bool animated;
  float offsetX;
  float offsetY;
  map<Direction, bool> sameTileMap;
  json autoTileData;
  sf::IntRect getAutoTileCornerImageBounds(int index, string corner, Direction cornerDirection, int ox, int oy);
  void setAutoTileData();
  void updateImages();
  void updateImageByFrame(int frame);

 public:
  TileSpriteManager(string spritesheetSrc, AutoTileType autoTileType, bool animated, float offsetX, float offsetY);
  virtual ~TileSpriteManager() = default;
  void updateSameTileMap(Direction direction, bool val);
  sf::Image getImage(int frame);
  float getOffsetX();
  float getOffsetY();
};

}  // namespace Backdrop

#endif
