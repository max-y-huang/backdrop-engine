#include "MapSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <memory>

using std::shared_ptr;

namespace Backdrop {

MapSpriteManager::MapSpriteManager(int width, int height) {
  tileSpriteManagers.resize(height);
  for (int y = 0; y < height; ++y) {
    tileSpriteManagers[y].resize(width);
    for (int x = 0; x < width; ++x) {
      tileSpriteManagers[y][x].resize(3);
    }
  }
};

void MapSpriteManager::setTileSpriteManager(shared_ptr<TileSpriteManager> manager, int x, int y, int layer) {
  tileSpriteManagers[y][x][layer] = manager;
  updateTexture();
}

void MapSpriteManager::updateTexture() {
  int height = tileSpriteManagers.size();
  int width = tileSpriteManagers[0].size();
  // Create image.
  sf::Image image;
  image.create(48 * width, 48 * height);
  // Add tile images to image.
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int layer = 0; layer < 3; ++layer) {
        if (tileSpriteManagers[y][x][layer]) {
          sf::Image tileImage = tileSpriteManagers[y][x][layer]->getImage();
          image.copy(tileImage, x * 48, y * 48, sf::IntRect{0, 0, 48, 48}, true);
        }
      }
    }
  }
  // Set texture.
  texture.create(48 * width, 48 * height);
  texture.update(image, 0, 0);
}

sf::Sprite MapSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}

void MapSpriteManager::onNotify(shared_ptr<Observer::State> state) {
}

}  // namespace Backdrop
