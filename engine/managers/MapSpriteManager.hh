#ifndef MAP_SPRITE_MANAGER_HH
#define MAP_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <vector>

#include "../maps/Tile.hh"
#include "SpriteManager.hh"
#include "TileSpriteManager.hh"

using std::map;
using std::string;
using std::vector;

namespace Backdrop {

class MapSpriteManager final : public SpriteManager {
  sf::Texture texture;
  vector<vector<vector<shared_ptr<Tile>>>> &tiles;
  void onNotify(shared_ptr<Observer::State> state);

 public:
  MapSpriteManager(vector<vector<vector<shared_ptr<Tile>>>> &tiles);
  sf::Sprite getSprite();
  void updateSprite();
};

}  // namespace Backdrop

#endif
