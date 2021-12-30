#ifndef FIELD_SPRITE_MANAGER_HH
#define FIELD_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#include "../core/Observer.hh"
#include "../enums.h"

using std::map;
using std::shared_ptr;

namespace Backdrop {

class FieldSpriteManager : public Observer {
  sf::Texture walkTexture;
  sf::Texture damageTexture;
  bool moved = false;
  Direction direction = Direction::Up;
  int walkFrameCount = 0;
  int walkAnimationFrame = 0;
  int walkAnimationSpeed = 8;
  map<Direction, int> directionOrder{
      {Direction::Up, 3},
      {Direction::Down, 0},
      {Direction::Left, 1},
      {Direction::Right, 2},
  };
  map<int, int> walkAnimationFrameColumn{
      {0, 1},
      {1, 0},
      {2, 1},
      {3, 2},
  };
  void onNotify(shared_ptr<Observer::State> state);

 public:
  FieldSpriteManager();
  sf::Sprite getSprite();
};

}  // namespace Backdrop

#endif
