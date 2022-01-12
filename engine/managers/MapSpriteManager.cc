#include "MapSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "../maps/Tile.hh"

using std::shared_ptr;

namespace Backdrop {

MapSpriteManager::MapSpriteManager(vector<vector<vector<shared_ptr<Tile>>>> &tiles) : tiles{tiles} {};

void MapSpriteManager::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    if (animationClock.getElapsedTime().asMicroseconds() >= 1000000.0 / animationSpeed) {
      animationFrame = (animationFrame + 1) % 4;
      animationClock.restart();
      updateSprite();
    }
  }
}

void MapSpriteManager::updateSprite() {
  int height = tiles.size();
  int width = tiles[0].size();
  // Create image.
  sf::Image image;
  image.create(48 * width, 48 * height + 48);
  // Add tile images to image.
  for (int layer = 0; layer < 3; ++layer) {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        if (tiles[y][x][layer]) {
          int frame = animationFrameColumn[animationFrame];
          sf::Image tileImage = tiles[y][x][layer]->spriteManager->getImage(frame);
          image.copy(tileImage, x * 48, y * 48, sf::IntRect{0, 0, 48, 96}, true);
        }
      }
    }
  }
  // Set texture.
  texture.loadFromImage(image);
}

sf::Sprite MapSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}

}  // namespace Backdrop
