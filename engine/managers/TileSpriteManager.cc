#include "TileSpriteManager.hh"

#include <SFML/Graphics.hpp>

namespace Backdrop {

TileSpriteManager::TileSpriteManager(string spritesheetSrc, Tileset tileset, int index) : tileset{tileset}, index{index} {
  texture.loadFromFile(spritesheetSrc);
}

void TileSpriteManager::onNotify(shared_ptr<Observer::State> state) {
}

sf::Sprite TileSpriteManager::getSprite() {
  if (tileset.isAutoTiles()) {
    int x = 2 * (index % tileset.getWidth());
    int y = 3 * (index / tileset.getWidth());
    sf::Sprite sprite{texture, sf::IntRect(48 * x, 48 * y, 48, 48)};
    return sprite;
  } else {
    int x = (index % tileset.getWidth());
    int y = (index / tileset.getWidth());
    sf::Sprite sprite{texture, sf::IntRect(48 * x, 48 * y, 48, 48)};
    return sprite;
  }
}

}  // namespace Backdrop
