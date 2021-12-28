#include "View.hh"

#include <SFML/Graphics.hpp>

#include "../controllers/Clock.hh"

namespace Backdrop {

void View::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    render(clockState);
  }
}

}  // namespace Backdrop
