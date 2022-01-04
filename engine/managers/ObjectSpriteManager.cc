#include "ObjectSpriteManager.hh"

namespace Backdrop {

ObjectSpriteManager::ObjectSpriteManager() {
  texture.create(48, 48);
  // texture.loadFromFile("assets/images/system/shadow.png");
}

sf::Sprite ObjectSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}

}  // namespace Backdrop
