#include "ObjectView.hh"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <vector>

#include "../controllers/Clock.hh"
#include "../core/Debugger.hh"
#include "../objects/Character.hh"
#include "../objects/Object.hh"

using std::vector;

namespace Backdrop {

ObjectView::ObjectView(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Object>>& objects) : objects{objects} {
  window = _window;
  shadowTexture.loadFromFile("assets/images/system/shadow.png");
  sf::Image collisionBoxImage;
  collisionBoxImage.create(48, 48, sf::Color::White);
  collisionBoxTexture.loadFromImage(collisionBoxImage);
}

void ObjectView::renderCollisionBoxes() {
  for (auto object : objects) {
    for (auto collisionBox : object->collisionBoxes) {
      sf::Sprite sprite{collisionBoxTexture};
      sprite.setTextureRect(sf::IntRect{0, 0, int(collisionBox->width), int(collisionBox->height)});
      sprite.setPosition(collisionBox->getGlobalX(), collisionBox->getGlobalY());
      sprite.setColor(sf::Color{255, 0, 255, 84});
      window->draw(sprite);
    }
  }
}

void ObjectView::renderShadows() {
  for (auto object : objects) {
    if (object->isVisible()) {
      auto character = std::dynamic_pointer_cast<Character>(object);
      float x = object->position.getX();
      float y = object->position.getY();
      if (character) {
        sf::Sprite sprite{shadowTexture};
        sprite.setPosition(x, y);
        window->draw(sprite);
      }
    }
  }
}

void ObjectView::renderObjects() {
  std::sort(objects.begin(), objects.end(), [](auto a, auto b) {
    return a->position.getY() < b->position.getY();
  });
  for (auto object : objects) {
    if (object->isVisible()) {
      auto character = std::dynamic_pointer_cast<Character>(object);
      float x = object->position.getX();
      float y = object->position.getY();
      sf::Sprite sprite = object->spriteManager->getSprite();
      sprite.setPosition(x, y);
      window->draw(sprite);
    }
  }
}

void ObjectView::render(shared_ptr<Clock::State> state) {
  renderShadows();
  renderObjects();
  // if (Debugger::getInstance()->isDebugMode()) {
  //   renderCollisionBoxes();
  // }
}

}  // namespace Backdrop
