#ifndef CLOCK_HH
#define CLOCK_HH

#include <SFML/Graphics.hpp>
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
  shared_ptr<sf::RenderWindow> window;
  int frameCount;
  sf::Clock clock;

 public:
  Clock(shared_ptr<sf::RenderWindow> window, int fps);
  void update();
};

}  // namespace Backdrop

#endif
