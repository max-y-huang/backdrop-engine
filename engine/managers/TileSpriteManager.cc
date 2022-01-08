#include "TileSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>

#include "../enums.hh"

using std::string;

namespace Backdrop {

TileSpriteManager::TileSpriteManager(int index, bool autoTile, int tilesetWidth, string spritesheetSrc) : index{index}, autoTile{autoTile}, tilesetWidth{tilesetWidth} {
  spritesheetImage.loadFromFile(spritesheetSrc);
  if (autoTile) {
    setAutoTileData();
  }
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
  int ox = 2 * (index % tilesetWidth);
  int oy = 3 * (index / tilesetWidth);
  int x = 48 * ox + 24 * int(data["x"]);
  int y = 48 * oy + 24 * int(data["y"]);
  return sf::IntRect{x, y, 24, 24};
}

void TileSpriteManager::updateImage() {
  // Reset image.
  image.create(48, 48);
  // Add corners to image.
  if (autoTile) {
    auto topLeftBounds = getAutoTileCornerImageBounds(index, "topLeft", Direction::UpLeft);
    auto topRightBounds = getAutoTileCornerImageBounds(index, "topRight", Direction::UpRight);
    auto bottomLeftBounds = getAutoTileCornerImageBounds(index, "bottomLeft", Direction::DownLeft);
    auto bottomRightBounds = getAutoTileCornerImageBounds(index, "bottomRight", Direction::DownRight);
    image.copy(spritesheetImage, 0, 0, topLeftBounds);
    image.copy(spritesheetImage, 24, 0, topRightBounds);
    image.copy(spritesheetImage, 0, 24, bottomLeftBounds);
    image.copy(spritesheetImage, 24, 24, bottomRightBounds);
  } else {
    int x = (index % tilesetWidth);
    int y = (index / tilesetWidth);
    image.copy(spritesheetImage, 0, 0, sf::IntRect{48 * x, 48 * y, 48, 48});
  }
}

sf::Image TileSpriteManager::getImage() {
  return image;
}

}  // namespace Backdrop
