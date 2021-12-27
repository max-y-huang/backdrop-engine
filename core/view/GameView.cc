#include "GameView.hh"

#include "../Clock.hh"

namespace PonchoEngine {

GameView::GameView(shared_ptr<sf::RenderWindow> _window) {
  window = _window;
}

void GameView::render(shared_ptr<Clock::State> state) {
  sf::CircleShape shape(100.f);
  switch (state->frameCount % 3) {
    case 0:
      shape.setFillColor(sf::Color::Red);
      break;
    case 1:
      shape.setFillColor(sf::Color::Green);
      break;
    default:
      shape.setFillColor(sf::Color::Blue);
      break;
  }
  window->draw(shape);
}

}  // namespace PonchoEngine
