#include "TileSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "../enums.hh"

using std::string;

namespace Backdrop {

TileSpriteManager::TileSpriteManager(AutoTileType autoTileType, string spritesheetSrc) : autoTileType{autoTileType} {
  spritesheetImage.loadFromFile(spritesheetSrc);
  setAutoTileData();
  updateImage();
}

void TileSpriteManager::setAutoTileData() {
  std::ifstream file{"config/autoTile.json"};
  file >> autoTileData;
}

void TileSpriteManager::updateSameTileMap(Direction direction, bool val) {
  sameTileMap[direction] = val;
  updateImage();
}

sf::IntRect TileSpriteManager::getAutoTileCornerImageBounds(int index, string corner, Direction cornerDirection) {
  Direction yDirection = static_cast<Direction>((cornerDirection - 4) / 2);      // Get Up/Down from corner direction.
  Direction xDirection = static_cast<Direction>((cornerDirection - 4) % 2 + 2);  // Get Left/Right from corner direction.
  auto data = autoTileData[corner][!sameTileMap[cornerDirection] * 4 +
                                   !sameTileMap[yDirection] * 2 +
                                   !sameTileMap[xDirection]];
  return sf::IntRect{24 * int(data["x"]), 24 * int(data["y"]), 24, 24};
}

void TileSpriteManager::updateImage() {
  // Reset image.
  image.create(48, 96);
  // Add corners to image.
  if (autoTileType == AutoTileType::NoAutoTile) {
    image.copy(spritesheetImage, 0, 0, sf::IntRect{0, 0, 48, 48});
  } else {
    auto topLeftBounds = getAutoTileCornerImageBounds(index, "topLeft", Direction::UpLeft);
    auto topRightBounds = getAutoTileCornerImageBounds(index, "topRight", Direction::UpRight);
    auto bottomLeftBounds = getAutoTileCornerImageBounds(index, "bottomLeft", Direction::DownLeft);
    auto bottomRightBounds = getAutoTileCornerImageBounds(index, "bottomRight", Direction::DownRight);
    image.copy(spritesheetImage, 0, 0, topLeftBounds);
    image.copy(spritesheetImage, 24, 0, topRightBounds);
    image.copy(spritesheetImage, 0, 24, bottomLeftBounds);
    image.copy(spritesheetImage, 24, 24, bottomRightBounds);
    if (autoTileType == AutoTileType::Wall && !sameTileMap[Direction::Down]) {
      if (!sameTileMap[Direction::Left]) {
        image.copy(spritesheetImage, 0, 48, sf::IntRect{0, 144, 24, 48});
      } else {
        image.copy(spritesheetImage, 0, 48, sf::IntRect{48, 144, 24, 48});
      }
      if (!sameTileMap[Direction::Right]) {
        image.copy(spritesheetImage, 24, 48, sf::IntRect{72, 144, 24, 48});
      } else {
        image.copy(spritesheetImage, 24, 48, sf::IntRect{24, 144, 24, 48});
      }
    }
  }
}

sf::Image TileSpriteManager::getImage() {
  return image;
}

}  // namespace Backdrop
