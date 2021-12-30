#include "Clock.hh"

#include <SFML/System/Clock.hpp>
#include <memory>

#include "../core/Observer.hh"

using std::shared_ptr;

namespace Backdrop {

Clock::Clock(int fps) : frameCount{0}, tickLength{1000000.0 / fps} {
  clock.restart();
}

void Clock::update() {
  sf::Time elapsed = clock.getElapsedTime();
  if (elapsed.asMicroseconds() >= tickLength) {
    clock.restart();
    ++frameCount;
    notifyObservers(std::make_shared<Clock::State>(frameCount, elapsed.asMicroseconds()));
  }
}

}  // namespace Backdrop
