#include "Clock.hh"

#include <SFML/System.hpp>
#include <memory>

#include "../core/Observer.hh"

using std::shared_ptr;

namespace Backdrop {

Clock::Clock(int fps) : frameCount{0}, tickLength{1000 / fps} {
  clock.restart();
}

shared_ptr<Observer::State> Clock::getState() {
  return std::make_shared<Clock::State>(frameCount);
}

void Clock::update() {
  sf::Time elapsed = clock.getElapsedTime();
  if (elapsed.asMilliseconds() >= tickLength) {
    clock.restart();
    ++frameCount;
    notifyObservers();
  }
}

}  // namespace Backdrop
