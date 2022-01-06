#include "ObjectView.hh"

#include <SFML/Graphics.hpp>
#include <vector>

#include "../controllers/Clock.hh"
#include "../objects/Object.hh"
#include "../objects/Character.hh"

using std::vector;

namespace Backdrop {

ObjectView::ObjectView(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Object>>& objects) : objects{objects} {
  window = _window;
  shadowTexture.loadFromFile("assets/images/system/shadow.png");
}

void ObjectView::render(shared_ptr<Clock::State> state) {
  for (auto object : objects) {
    auto character = std::dynamic_pointer_cast<Character>(object);
    float x = object->position.getX() * 48;
    float y = object->position.getY() * 48;
    // Render shadow if character.
    if (character) {
      sf::Sprite shadowSprite{shadowTexture};
      shadowSprite.setPosition(x, y);
      window->draw(shadowSprite);
    }
    sf::Sprite sprite = object->spriteManager->getSprite();
    sprite.setPosition(x, y);
    window->draw(sprite);
  }
}

}  // namespace Backdrop
