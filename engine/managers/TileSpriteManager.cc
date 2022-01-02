#include "TileSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>

#include "../enums.h"

using std::map;
using std::pair;
using std::string;

namespace Backdrop {

TileSpriteManager::TileSpriteManager(int index, bool autoTile, int tilesetWidth, string spritesheetSrc) : index{index}, autoTile{autoTile}, tilesetWidth{tilesetWidth} {
  spritesheetImage.loadFromFile(spritesheetSrc);
  if (autoTile) {
    createAutoTileCornerImageMap();
  }
  updateTexture();
}

void TileSpriteManager::createAutoTileCornerImageMap() {
  autoTileCornerImageMap[Direction::UpLeft][true][true][true] = {2, 4};
  autoTileCornerImageMap[Direction::UpLeft][true][true][false] = {0, 4};
  autoTileCornerImageMap[Direction::UpLeft][true][false][true] = {2, 2};
  autoTileCornerImageMap[Direction::UpLeft][true][false][false] = {0, 2};
  autoTileCornerImageMap[Direction::UpLeft][false][true][true] = {2, 0};
  autoTileCornerImageMap[Direction::UpLeft][false][true][false] = {0, 4};
  autoTileCornerImageMap[Direction::UpLeft][false][false][true] = {2, 2};
  autoTileCornerImageMap[Direction::UpLeft][false][false][false] = {0, 2};
  autoTileCornerImageMap[Direction::UpRight][true][true][true] = {1, 4};
  autoTileCornerImageMap[Direction::UpRight][true][true][false] = {3, 4};
  autoTileCornerImageMap[Direction::UpRight][true][false][true] = {1, 2};
  autoTileCornerImageMap[Direction::UpRight][true][false][false] = {3, 2};
  autoTileCornerImageMap[Direction::UpRight][false][true][true] = {3, 0};
  autoTileCornerImageMap[Direction::UpRight][false][true][false] = {3, 4};
  autoTileCornerImageMap[Direction::UpRight][false][false][true] = {1, 2};
  autoTileCornerImageMap[Direction::UpRight][false][false][false] = {3, 2};
  autoTileCornerImageMap[Direction::DownLeft][true][true][true] = {2, 3};
  autoTileCornerImageMap[Direction::DownLeft][true][true][false] = {0, 3};
  autoTileCornerImageMap[Direction::DownLeft][true][false][true] = {2, 5};
  autoTileCornerImageMap[Direction::DownLeft][true][false][false] = {0, 5};
  autoTileCornerImageMap[Direction::DownLeft][false][true][true] = {2, 1};
  autoTileCornerImageMap[Direction::DownLeft][false][true][false] = {0, 3};
  autoTileCornerImageMap[Direction::DownLeft][false][false][true] = {2, 5};
  autoTileCornerImageMap[Direction::DownLeft][false][false][false] = {0, 5};
  autoTileCornerImageMap[Direction::DownRight][true][true][true] = {1, 3};
  autoTileCornerImageMap[Direction::DownRight][true][true][false] = {3, 3};
  autoTileCornerImageMap[Direction::DownRight][true][false][true] = {1, 5};
  autoTileCornerImageMap[Direction::DownRight][true][false][false] = {3, 5};
  autoTileCornerImageMap[Direction::DownRight][false][true][true] = {3, 1};
  autoTileCornerImageMap[Direction::DownRight][false][true][false] = {3, 3};
  autoTileCornerImageMap[Direction::DownRight][false][false][true] = {1, 5};
  autoTileCornerImageMap[Direction::DownRight][false][false][false] = {3, 5};
}

void TileSpriteManager::onNotify(shared_ptr<Observer::State> state) {
}

void TileSpriteManager::updateSameTileMap(Direction direction, bool val) {
  sameTileMap[direction] = val;
  updateTexture();
}

void TileSpriteManager::updateTexture() {
  sf::Image image;
  image.create(48, 48);
  if (autoTile) {
    int x = 2 * (index % tilesetWidth);
    int y = 3 * (index / tilesetWidth);
    auto topLeftCoord = autoTileCornerImageMap[Direction::UpLeft][sameTileMap[Direction::UpLeft]][sameTileMap[Direction::Up]][sameTileMap[Direction::Left]];
    auto topRightCoord = autoTileCornerImageMap[Direction::UpRight][sameTileMap[Direction::UpRight]][sameTileMap[Direction::Up]][sameTileMap[Direction::Right]];
    auto bottomLeftCoord = autoTileCornerImageMap[Direction::DownLeft][sameTileMap[Direction::DownLeft]][sameTileMap[Direction::Down]][sameTileMap[Direction::Left]];
    auto bottomRightCoord = autoTileCornerImageMap[Direction::DownRight][sameTileMap[Direction::DownRight]][sameTileMap[Direction::Down]][sameTileMap[Direction::Right]];
    image.copy(spritesheetImage, 0, 0, sf::IntRect{48 * x + 24 * topLeftCoord.first, 48 * y + 24 * topLeftCoord.second, 24, 24});
    image.copy(spritesheetImage, 24, 0, sf::IntRect{48 * x + 24 * topRightCoord.first, 48 * y + 24 * topRightCoord.second, 24, 24});
    image.copy(spritesheetImage, 0, 24, sf::IntRect{48 * x + 24 * bottomLeftCoord.first, 48 * y + 24 * bottomLeftCoord.second, 24, 24});
    image.copy(spritesheetImage, 24, 24, sf::IntRect{48 * x + 24 * bottomRightCoord.first, 48 * y + 24 * bottomRightCoord.second, 24, 24});
  } else {
    int x = (index % tilesetWidth);
    int y = (index / tilesetWidth);
    image.copy(spritesheetImage, 0, 0, sf::IntRect{48 * x, 48 * y, 48, 48});
  }
  texture.create(48, 48);
  texture.update(image, 0, 0);
}

sf::Sprite TileSpriteManager::getSprite() {
  sf::Sprite sprite{texture};
  return sprite;
}

}  // namespace Backdrop
