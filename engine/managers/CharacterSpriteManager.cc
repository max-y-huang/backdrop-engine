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
  walkTexture.loadFromFile(spritesheetSrc);
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
      if (walkFrameCount % walkAnimationSpeed == 0) {
        walkAnimationFrame = (walkAnimationFrame + 1) % 4;
      }
      moved = true;
    }
  }
}

sf::Sprite CharacterSpriteManager::getSprite() {
  int x = 48 * walkAnimationFrameColumn[walkAnimationFrame];
  int y = 48 * directionOrder[direction];
  sf::Sprite sprite{walkTexture, sf::IntRect(x, y, 48, 48)};
  return sprite;
}

}  // namespace Backdrop
