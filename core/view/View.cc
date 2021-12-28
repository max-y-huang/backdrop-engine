#include "View.hh"

#include <SFML/Graphics.hpp>

#include "../Clock.hh"

namespace PonchoEngine {

void View::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    render(clockState);
  }
}

}  // namespace PonchoEngine
