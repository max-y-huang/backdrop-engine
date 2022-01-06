#include "ObjectView.hh"

#include <SFML/Graphics.hpp>
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
  sf::Image borderBoxImage;
  borderBoxImage.create(48, 48, sf::Color::White);
  borderBoxTexture.create(48, 48);
  borderBoxTexture.update(borderBoxImage, 0, 0);
}

void ObjectView::renderBorderBoxes() {
  for (auto object : objects) {
    auto character = std::dynamic_pointer_cast<Character>(object);
    float x = object->position.getX();
    float y = object->position.getY();
    sf::Sprite sprite{borderBoxTexture};
    sprite.setPosition(x, y);
    if (character) {
      sprite.setColor(sf::Color{0, 0, 255, 84});
    } else {
      sprite.setColor(sf::Color{255, 0, 0, 84});
    }
    window->draw(sprite);
  }
}

void ObjectView::renderShadows() {
  for (auto object : objects) {
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

void ObjectView::renderObjects() {
  for (auto object : objects) {
    auto character = std::dynamic_pointer_cast<Character>(object);
    float x = object->position.getX();
    float y = object->position.getY();
    sf::Sprite sprite = object->spriteManager->getSprite();
    sprite.setPosition(x, y);
    window->draw(sprite);
  }
}

void ObjectView::render(shared_ptr<Clock::State> state) {
  if (Debugger::getInstance()->isDebugMode()) {
    renderBorderBoxes();
  }
  renderShadows();
  renderObjects();
}

}  // namespace Backdrop
