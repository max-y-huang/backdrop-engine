#include "TileSpriteManager.hh"

#include <SFML/Graphics.hpp>

namespace Backdrop {

TileSpriteManager::TileSpriteManager(int index, bool autoTile, int tilesetWidth, string spritesheetSrc) : index{index}, autoTile{autoTile}, tilesetWidth{tilesetWidth} {
  texture.loadFromFile(spritesheetSrc);
}

void TileSpriteManager::onNotify(shared_ptr<Observer::State> state) {
}

sf::Sprite TileSpriteManager::getSprite() {
  if (autoTile) {
    int x = 2 * (index % tilesetWidth);
    int y = 3 * (index / tilesetWidth);
    sf::Sprite sprite{texture, sf::IntRect(48 * x, 48 * y, 48, 48)};
    return sprite;
  }
  int x = (index % tilesetWidth);
  int y = (index / tilesetWidth);
  sf::Sprite sprite{texture, sf::IntRect(48 * x, 48 * y, 48, 48)};
  return sprite;
}

}  // namespace Backdrop
