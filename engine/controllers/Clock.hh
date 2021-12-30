#ifndef CLOCK_HH
#define CLOCK_HH

#include <SFML/System/Clock.hpp>
#include <memory>

#include "../core/Observer.hh"

namespace Backdrop {

class Clock final : public Observer::Subject {
 public:
  struct State final : public Observer::State {
    int frameCount;
    sf::Int64 tickLength;
    State(int frameCount, sf::Int64 tickLength) : frameCount{frameCount}, tickLength{tickLength} {};
  };

 private:
  int frameCount;
  double tickLength;
  sf::Clock clock;

 public:
  Clock(int fps);
  void update();
};

}  // namespace Backdrop

#endif
