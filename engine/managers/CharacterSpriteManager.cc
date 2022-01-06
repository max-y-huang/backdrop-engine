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
  normalTexture.loadFromFile(spritesheetSrc);
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
  sf::Sprite sprite{normalTexture, sf::IntRect{48 * x, 48 * y, 48, 48}};
  return sprite;
}

}  // namespace Backdrop
