#ifndef TILE_SPRITE_MANAGER_HH
#define TILE_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <string>

#include "../maps/Tileset.hh"
#include "SpriteManager.hh"

using std::string;

namespace Backdrop {

class TileSpriteManager final : public SpriteManager {
  sf::Texture texture;
  Tileset tileset;
  int index;
  void onNotify(shared_ptr<Observer::State> state);

 public:
  TileSpriteManager(string spritesheetSrc, Tileset tileset, int index);
  sf::Sprite getSprite();
};

}  // namespace Backdrop

#endif
