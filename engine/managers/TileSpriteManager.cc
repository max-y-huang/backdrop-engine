#include "TileSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <memory>
#include <string>

#include "../core/Observer.hh"
#include "../enums.hh"

using std::shared_ptr;
using std::string;

namespace Backdrop {

TileSpriteManager::TileSpriteManager(string spritesheetSrc, AutoTileType autoTileType, bool animated) : autoTileType{autoTileType}, animated{animated} {
  spritesheetImage.loadFromFile(spritesheetSrc);
  setAutoTileData();
  images.resize(animated ? 3 : 1);
  updateImages();
}

void TileSpriteManager::setAutoTileData() {
  std::ifstream file{"config/autoTile.json"};
  file >> autoTileData;
}

void TileSpriteManager::updateSameTileMap(Direction direction, bool val) {
  sameTileMap[direction] = val;
  updateImages();
}

sf::IntRect TileSpriteManager::getAutoTileCornerImageBounds(int index, string corner, Direction cornerDirection, int ox, int oy) {
  Direction yDirection = static_cast<Direction>((cornerDirection - 4) / 2);      // Get Up/Down from corner direction.
  Direction xDirection = static_cast<Direction>((cornerDirection - 4) % 2 + 2);  // Get Left/Right from corner direction.
  auto data = autoTileData[corner][!sameTileMap[cornerDirection] * 4 +
                                   !sameTileMap[yDirection] * 2 +
                                   !sameTileMap[xDirection]];
  return sf::IntRect{ox + 24 * int(data["x"]), oy + 24 * int(data["y"]), 24, 24};
}

void TileSpriteManager::updateImageByFrame(int frame) {
  bool isWall = (autoTileType == AutoTileType::Wall);
  int ox = frame * 96;
  int oy = 0;
  // Reset image.
  images[frame].create(48, isWall ? 96 : 48);
  // Add corners to image.
  if (autoTileType == AutoTileType::NoAutoTile) {
    images[frame].copy(spritesheetImage, 0, 0, sf::IntRect{ox, oy, 48, 48});
  } else {
    auto topLeftBounds = getAutoTileCornerImageBounds(index, "topLeft", Direction::UpLeft, ox, oy);
    auto topRightBounds = getAutoTileCornerImageBounds(index, "topRight", Direction::UpRight, ox, oy);
    auto bottomLeftBounds = getAutoTileCornerImageBounds(index, "bottomLeft", Direction::DownLeft, ox, oy);
    auto bottomRightBounds = getAutoTileCornerImageBounds(index, "bottomRight", Direction::DownRight, ox, oy);
    images[frame].copy(spritesheetImage, 0, 0, topLeftBounds);
    images[frame].copy(spritesheetImage, 24, 0, topRightBounds);
    images[frame].copy(spritesheetImage, 0, 24, bottomLeftBounds);
    images[frame].copy(spritesheetImage, 24, 24, bottomRightBounds);
    if (isWall && !sameTileMap[Direction::Down]) {
      if (!sameTileMap[Direction::Left]) {
        images[frame].copy(spritesheetImage, 0, 48, sf::IntRect{ox, oy + 144, 24, 48});
      } else {
        images[frame].copy(spritesheetImage, 0, 48, sf::IntRect{ox + 48, oy + 144, 24, 48});
      }
      if (!sameTileMap[Direction::Right]) {
        images[frame].copy(spritesheetImage, 24, 48, sf::IntRect{ox + 72, oy + 144, 24, 48});
      } else {
        images[frame].copy(spritesheetImage, 24, 48, sf::IntRect{ox + 24, oy + 144, 24, 48});
      }
    }
  }
}

void TileSpriteManager::updateImages() {
  if (animated) {
    for (int i = 0; i < 3; i++) {
      updateImageByFrame(i);
    }
  } else {
    updateImageByFrame(0);
  }
}

sf::Image TileSpriteManager::getImage(int frame) {
  if (animated) {
    return images[frame];
  }
  return images[0];
}

}  // namespace Backdrop
