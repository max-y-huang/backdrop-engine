#include "GameView.hh"

#include <SFML/Graphics.hpp>
#include <vector>

#include "../controllers/Clock.hh"
#include "../objects/Object.hh"

using std::vector;

namespace Backdrop {

GameView::GameView(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Object>>& objects) : objects{objects} {
  window = _window;
}

void GameView::render(shared_ptr<Clock::State> state) {
  for (auto object : objects) {
    sf::Sprite sprite = object->spriteManager->getSprite();
    sprite.setPosition(object->position.getX() * 48, object->position.getY() * 48);
    window->draw(sprite);
  }
}

}  // namespace Backdrop
