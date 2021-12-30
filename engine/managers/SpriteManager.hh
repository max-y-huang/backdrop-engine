#ifndef SPRITE_MANAGER_HH
#define SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>

#include "../core/Observer.hh"

namespace Backdrop {

class SpriteManager : public Observer {
 protected:
  virtual void onNotify(shared_ptr<Observer::State> state) = 0;

 public:
  virtual ~SpriteManager() = default;
  virtual sf::Sprite getSprite() = 0;
};

}  // namespace Backdrop

#endif
