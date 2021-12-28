#include "GameView.hh"

#include <vector>

#include "../Clock.hh"
#include "../object/Object.hh"

using std::vector;

namespace PonchoEngine {

GameView::GameView(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Object>>& objects) : objects{objects} {
  window = _window;
}

void GameView::render(shared_ptr<Clock::State> state) {
  for (auto object : objects) {
    sf::RectangleShape shape{sf::Vector2f{32, 32}};
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(object->position.x * 32, object->position.y * 32);
    window->draw(shape);
  }
}

}  // namespace PonchoEngine
