#include "EraseView.hh"

#include "../Clock.hh"

namespace PonchoEngine {

EraseView::EraseView(shared_ptr<sf::RenderWindow> _window) {
  window = _window;
}

void EraseView::render(shared_ptr<Clock::State> state) {
  window->clear();
}

}  // namespace PonchoEngine
