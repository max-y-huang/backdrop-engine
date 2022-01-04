#include "MapSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "../maps/Tile.hh"

using std::shared_ptr;

namespace Backdrop {

MapSpriteManager::MapSpriteManager(vector<vector<vector<shared_ptr<Tile>>>> &tiles) : tiles{tiles} {};

void MapSpriteManager::updateSprite() {
  int height = tiles.size();
  int width = tiles[0].size();
  // Create image.
  sf::Image image;
  image.create(48 * width, 48 * height);
  // Add tile images to image.
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      for (int layer = 0; layer < 3; ++layer) {
        if (tiles[y][x][layer]) {
          sf::Image tileImage = tiles[y][x][layer]->spriteManager->getImage();
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

}  // namespace Backdrop
