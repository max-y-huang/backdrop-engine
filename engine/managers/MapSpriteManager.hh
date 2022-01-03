#ifndef MAP_SPRITE_MANAGER_HH
#define MAP_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <vector>

#include "SpriteManager.hh"
#include "TileSpriteManager.hh"

using std::map;
using std::string;
using std::vector;

namespace Backdrop {

class MapSpriteManager final : public SpriteManager {
  sf::Texture texture;
  vector<vector<vector<shared_ptr<TileSpriteManager>>>> tileSpriteManagers;
  void onNotify(shared_ptr<Observer::State> state);
  void updateTexture();

 public:
  MapSpriteManager(int width, int height);
  sf::Sprite getSprite();
  void setTileSpriteManager(shared_ptr<TileSpriteManager> manager, int x, int y, int layer);
};

}  // namespace Backdrop

#endif
