#ifndef MAP_SPRITE_MANAGER_HH
#define MAP_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <vector>

#include "../maps/Tile.hh"
#include "TileSpriteManager.hh"

using std::map;
using std::string;
using std::vector;

namespace Backdrop {

class MapSpriteManager final {
  sf::Texture texture;
  vector<vector<vector<shared_ptr<Tile>>>> &tiles;

 public:
  MapSpriteManager(vector<vector<vector<shared_ptr<Tile>>>> &tiles);
  sf::Sprite getSprite();
  void updateSprite();
};

}  // namespace Backdrop

#endif
