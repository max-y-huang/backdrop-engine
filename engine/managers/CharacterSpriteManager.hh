#ifndef CHARACTER_SPRITE_MANAGER_HH
#define CHARACTER_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <map>
#include <memory>
#include <string>

#include "../core/Observer.hh"
#include "../enums.h"
#include "ObjectSpriteManager.hh"

using std::map;
using std::shared_ptr;
using std::string;

namespace Backdrop {

class CharacterSpriteManager final : public ObjectSpriteManager {
  sf::Clock animationClock;
  sf::Texture texture;
  bool moved = false;
  Direction direction = Direction::Up;
  int walkFrameCount = -1;
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
  CharacterSpriteManager(string spritesheetSrc);
  sf::Sprite getSprite();
};

}  // namespace Backdrop

#endif
