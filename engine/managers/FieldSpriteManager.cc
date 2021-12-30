#include "FieldSpriteManager.hh"

#include <SFML/Graphics.hpp>

#include "../controllers/Clock.hh"
#include "../core/Observer.hh"
#include "../enums.h"
#include "../objects/Object.hh"

namespace Backdrop {

FieldSpriteManager::FieldSpriteManager() {
  walkTexture.loadFromFile("assets/images/topdowns/male_walk.png");
}

void FieldSpriteManager::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  auto objectState = std::dynamic_pointer_cast<Object::State>(state);
  if (clockState) {
    if (!moved) {
      walkAnimationFrame = 0;
      walkFrameCount = -1;
    }
    moved = false;
  }
  if (objectState) {
    // Handle walkAnimationFrame.
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

sf::Sprite FieldSpriteManager::getSprite() {
  int x = 48 * walkAnimationFrameColumn[walkAnimationFrame];
  int y = 48 * directionOrder[direction];
  sf::Sprite sprite{walkTexture, sf::IntRect(x, y, 48, 48)};
  return sprite;
}

}  // namespace Backdrop
