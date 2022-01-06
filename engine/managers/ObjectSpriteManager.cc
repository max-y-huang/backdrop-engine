#include "ObjectSpriteManager.hh"

namespace Backdrop {

ObjectSpriteManager::ObjectSpriteManager() {
  texture.create(48, 48);
}

sf::Sprite ObjectSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}

}  // namespace Backdrop
