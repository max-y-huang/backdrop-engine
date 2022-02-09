#ifndef MAP_SPRITE_MANAGER_HH
#define MAP_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

#include "../controllers/Clock.hh"
#include "../core/Observer.hh"
#include "../maps/Tile.hh"
#include "TileSpriteManager.hh"

using std::map;
using std::string;
using std::vector;

namespace Backdrop {

class MapSpriteManager final : public Observer {
  sf::Clock animationClock;
  vector<sf::Texture> textures;
  vector<sf::Texture> overheadTextures;
  vector<vector<vector<shared_ptr<Tile>>>> &tiles;
  void onNotify(shared_ptr<Observer::State> state);
  void updateSpriteByFrame(int frame);
  int animationFrame = 0;
  int animationSpeed = 3;
  map<int, int> animationFrameColumn{
      {0, 1},
      {1, 0},
      {2, 1},
      {3, 2},
  };

 public:
  MapSpriteManager(vector<vector<vector<shared_ptr<Tile>>>> &tiles);
  sf::Sprite getSprite();
  sf::Sprite getOverheadSprite();
  void updateSprites();
};

}  // namespace Backdrop

#endif
