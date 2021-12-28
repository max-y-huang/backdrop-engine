#include "Clock.hh"

#include <memory>

#include "../Observer.hh"

using std::shared_ptr;

namespace PonchoEngine {

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

}  // namespace PonchoEngine
