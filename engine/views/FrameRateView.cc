#include "FrameRateView.hh"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <string>

#include "../controllers/Clock.hh"
#include "../core/FrameRate.hh"

using std::string;

namespace Backdrop {

FrameRateView::FrameRateView(shared_ptr<sf::RenderWindow> _window) {
  window = _window;
}

void FrameRateView::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    render(clockState);
  }
}

void FrameRateView::render(shared_ptr<Clock::State> state) {
  if (state->frameCount % 60 == 0) {
    frameRate = FrameRate::getInstance()->getFrameRate();
  }
  sf::Font font;
  font.loadFromFile("assets/fonts/arial.ttf");
  sf::Text text;
  text.setFont(font);
  text.setString(std::to_string(int(round(frameRate))) + " FPS");
  text.setCharacterSize(14);
  text.setFillColor(sf::Color::Red);
  text.setPosition(window->getSize().x - text.getLocalBounds().width - 8, 8);
  window->draw(text);
}

}  // namespace Backdrop
