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
  loadImages(spritesheetSrc);
}

void CharacterSpriteManager::loadImages(string spritesheetSrc) {
  walkImage.loadFromFile(spritesheetSrc);
  shadowImage.loadFromFile("assets/images/system/shadow.png");
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
  // Create walk image.
  sf::Image image;
  image.create(48, 54);
  image.copy(shadowImage, 0, 0, sf::IntRect{0, 0, 48, 54});
  image.copy(walkImage, 0, 0, sf::IntRect{48 * x, 48 * y, 48, 48}, true);
  // Update walk texture.
  walkTexture.create(48, 54);
  walkTexture.update(image, 0, 0);
  // Return current sprite.
  sf::Sprite sprite{walkTexture};
  return sprite;
}

}  // namespace Backdrop
