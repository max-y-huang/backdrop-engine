#ifndef TILE_SPRITE_MANAGER_HH
#define TILE_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "../enums.h"
#include "SpriteManager.hh"

using std::map;
using std::string;

namespace Backdrop {

class TileSpriteManager final : public SpriteManager {
  sf::Image spritesheetImage;
  sf::Image image;

  int index;
  bool autoTile;
  int tilesetWidth;
  map<Direction, bool> sameTileMap;
  map<Direction, map<bool, map<bool, map<bool, pair<int, int>>>>> autoTileCornerImageMap;
  void onNotify(shared_ptr<Observer::State> state);
  void createAutoTileCornerImageMap();
  void updateImage();

 public:
  TileSpriteManager(int index, bool autoTile, int tilesetWidth, string spritesheetSrc);
  sf::Sprite getSprite();
  sf::Image getImage();
  void updateSameTileMap(Direction direction, bool val);
};

}  // namespace Backdrop

#endif
