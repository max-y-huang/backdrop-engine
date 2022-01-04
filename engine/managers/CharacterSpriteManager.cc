#include "CharacterSpriteManager.hh"

#include <SFML/Graphics.hpp>
#include <string>

#include "../controllers/Clock.hh"
#include "../core/Observer.hh"
#include "../enums.h"
#include "../objects/Object.hh"

using std::string;

namespace Backdrop {

CharacterSpriteManager::CharacterSpriteManager(string spritesheetSrc) {
  animationClock.restart();
  setNormalTexture(spritesheetSrc);
}

void CharacterSpriteManager::setNormalTexture(string spritesheetSrc) {
  sf::Image shadowImage;
  shadowImage.loadFromFile("assets/images/system/shadow.png");
  sf::Image spritesheetImage;
  spritesheetImage.loadFromFile(spritesheetSrc);
  // Create texture image.
  sf::Image image;
  image.create(3 * 48, 4 * 54);
  for (int y = 0; y < 4; ++y) {
    for (int x = 0; x < 3; ++x) {
      image.copy(shadowImage, x * 48, y * 54, sf::IntRect{0, 0, 48, 54});
      image.copy(spritesheetImage, x * 48, y * 54, sf::IntRect{x * 48, y * 48, 48, 48}, true);
    }
  }
  // Update texture.
  normalTexture.create(3 * 48, 4 * 54);
  normalTexture.update(image, 0, 0);
}

void CharacterSpriteManager::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  auto objectState = std::dynamic_pointer_cast<Object::State>(state);
  if (clockState) {
    // Reset walk animation.
    if (!moved) {
      walkAnimationFrame = 0;
      walkFrameCount = -1;
    }
    moved = false;
  }
  if (objectState) {
    // Handle walk animation.
    if (objectState->type == "move") {
      ++walkFrameCount;
      direction = objectState->direction;
      if (animationClock.getElapsedTime().asMicroseconds() >= 1000000.0 / walkAnimationSpeed) {
        walkAnimationFrame = (walkAnimationFrame + 1) % 4;
        animationClock.restart();
      }
      moved = true;
    }
  }
}

sf::Sprite CharacterSpriteManager::getSprite() {
  int x = walkAnimationFrameColumn[walkAnimationFrame];
  int y = directionOrder[direction];
  sf::Sprite sprite{normalTexture, sf::IntRect{48 * x, 54 * y, 48, 54}};
  return sprite;
}

}  // namespace Backdrop
