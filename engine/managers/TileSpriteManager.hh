#ifndef TILE_SPRITE_MANAGER_HH
#define TILE_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <string>

#include "../maps/Tileset.hh"
#include "SpriteManager.hh"

using std::string;

namespace Backdrop {

class TileSpriteManager final : public SpriteManager {
  int index;
  bool autoTile;
  int tilesetWidth;
  sf::Texture texture;
  void onNotify(shared_ptr<Observer::State> state);

 public:
  TileSpriteManager(int index, bool autoTile, int tilesetWidth, string spritesheetSrc);
  sf::Sprite getSprite();
};

}  // namespace Backdrop

#endif
