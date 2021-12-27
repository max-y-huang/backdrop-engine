#ifndef CLOCK_HH
#define CLOCK_HH

#include <SFML/System.hpp>
#include <chrono>
#include <memory>

#include "Observer.hh"

namespace PonchoEngine {

class Clock final : public Observer::Subject {
  int frameCount;
  int tickLength;
  sf::Clock clock;
  shared_ptr<Observer::State> getState();

 public:
  struct State final : public Observer::State {
    int frameCount;
    State(int frameCount) : frameCount{frameCount} {};
  };
  Clock(int fps);
  void update();
};

}  // namespace PonchoEngine

#endif
