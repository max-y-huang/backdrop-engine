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
  sf::Image overheadImage;
  image.create(48 * width, 48 * height, sf::Color(0, 0, 0, 0));
  overheadImage.create(48 * width, 48 * height, sf::Color(0, 0, 0, 0));
  // Add tile images to image.
  for (int layer = 0; layer < 3; ++layer) {
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        if (tiles[y][x][layer]) {
          int frame = animationFrameColumn[animationFrame];
          sf::Image tileImage = tiles[y][x][layer]->spriteManager->getImage(frame);
          sf::Image overheadTileImage = tiles[y][x][layer]->spriteManager->getOverheadImage(frame);
          float offsetX = tiles[y][x][layer]->spriteManager->getOffsetX();
          float offsetY = tiles[y][x][layer]->spriteManager->getOffsetY();
          int cropX = 0;
          int cropY = 0;
          int cropWidth = tileImage.getSize().x;
          int cropHeight = tileImage.getSize().y;
          float drawX = x * 48 + offsetX;
          float drawY = y * 48 + offsetY;
          if (drawX < 0) {
            cropX -= drawX;
            cropWidth += drawX;
            drawX = 0;
          }
          if (drawX + cropWidth >= width * 48) {
            cropWidth = width * 48 - drawX;
          }
          if (drawY < 0) {
            cropY -= drawY;
            cropHeight += drawY;
            drawY = 0;
          }
          if (drawY + cropHeight >= height * 48) {
            cropHeight = height * 48 - drawY;
          }
          image.copy(tileImage, drawX, drawY, sf::IntRect{cropX, cropY, cropWidth, cropHeight}, true);
          overheadImage.copy(overheadTileImage, drawX, drawY, sf::IntRect{cropX, cropY, cropWidth, cropHeight}, true);
        }
      }
    }
  }
  // Set texture.
  texture.loadFromImage(image);
  overheadTexture.loadFromImage(overheadImage);
}

sf::Sprite MapSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}
sf::Sprite MapSpriteManager::getOverheadSprite() {
  sf::Sprite sprite{overheadTexture};
  return sprite;
}

}  // namespace Backdrop
