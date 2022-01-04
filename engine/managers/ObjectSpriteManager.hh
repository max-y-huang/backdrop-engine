#ifndef OBJECT_SPRITE_MANAGER_HH
#define OBJECT_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>

#include "../core/Observer.hh"

namespace Backdrop {

class ObjectSpriteManager : public Observer {
 protected:
  virtual void onNotify(shared_ptr<Observer::State> state) = 0;

 public:
  virtual ~ObjectSpriteManager() = default;
  virtual sf::Sprite getSprite() = 0;
};

}  // namespace Backdrop

#endif
