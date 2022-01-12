#ifndef TILE_SPRITE_MANAGER_HH
#define TILE_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <map>
#include <memory>
#include <string>

#include "../../lib/nlohmann/json.hpp"
#include "../core/Observer.hh"
#include "../enums.hh"

using nlohmann::json;
using std::map;
using std::shared_ptr;
using std::string;

namespace Backdrop {

class TileSpriteManager final : public Observer {
  sf::Clock animationClock;
  sf::Image spritesheetImage;
  sf::Image image;
  int index;
  AutoTileType autoTileType;
  bool animated;
  map<Direction, bool> sameTileMap;
  json autoTileData;
  int animationFrame = 0;
  int animationSpeed = 8;
  map<int, float> animationFrameColumn{
      {0, 1.5},
      {1, 1.5},
      {2, 1.5},
      {3, 1.5},
  };
  void onNotify(shared_ptr<Observer::State> state);
  sf::IntRect getAutoTileCornerImageBounds(int index, string corner, Direction cornerDirection, int ox, int oy);
  void setAutoTileData();
  void updateImage();

 public:
  TileSpriteManager(string spritesheetSrc, AutoTileType autoTileType, bool animated);
  virtual ~TileSpriteManager() = default;
  void updateSameTileMap(Direction direction, bool val);
  sf::Image getImage();
};

}  // namespace Backdrop

#endif
