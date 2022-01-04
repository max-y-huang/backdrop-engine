#ifndef OBJECT_SPRITE_MANAGER_HH
#define OBJECT_SPRITE_MANAGER_HH

#include <SFML/Graphics.hpp>

#include "../core/Observer.hh"

namespace Backdrop {

class ObjectSpriteManager : public Observer {
 protected:
  sf::Texture texture;
  virtual void onNotify(shared_ptr<Observer::State> state){};

 public:
  ObjectSpriteManager();
  virtual ~ObjectSpriteManager() = default;
  virtual sf::Sprite getSprite();
};

}  // namespace Backdrop

#endif
