#include "ObjectSpriteManager.hh"

namespace Backdrop {

ObjectSpriteManager::ObjectSpriteManager() {
  sf::Image image;
  image.create(48, 48, sf::Color::Red);
  texture.create(48, 48);
  texture.update(image, 0, 0);
}

sf::Sprite ObjectSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}

}  // namespace Backdrop
