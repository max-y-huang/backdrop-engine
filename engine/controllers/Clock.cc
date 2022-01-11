#include "Clock.hh"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <memory>

#include "../core/Observer.hh"

using std::shared_ptr;

namespace Backdrop {

Clock::Clock(shared_ptr<sf::RenderWindow> window, int fps) : window{window}, frameCount{0} {
  window->setFramerateLimit(fps);
  clock.restart();
}

void Clock::update() {
  sf::Time elapsed = clock.getElapsedTime();
  clock.restart();
  ++frameCount;
  notifyObservers(std::make_shared<Clock::State>(frameCount, elapsed.asMicroseconds()));
}

}  // namespace Backdrop
