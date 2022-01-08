#ifndef TILE_SPRITE_MANAGER_HH
#define TILE_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../../lib/nlohmann/json.hpp"
#include "../enums.hh"

using nlohmann::json;
using std::map;
using std::string;

namespace Backdrop {

class TileSpriteManager final {
  sf::Image spritesheetImage;
  sf::Image image;

  int index;
  bool autoTile;
  int tilesetWidth;
  map<Direction, bool> sameTileMap;
  json autoTileData;
  sf::IntRect getAutoTileCornerImageBounds(int index, string corner, Direction cornerDireciotn);
  void setAutoTileData();
  void updateImage();

 public:
  TileSpriteManager(int index, bool autoTile, int tilesetWidth, string spritesheetSrc);
  virtual ~TileSpriteManager() = default;
  void updateSameTileMap(Direction direction, bool val);
  sf::Image getImage();
};

}  // namespace Backdrop

#endif
