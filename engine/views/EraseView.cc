#include "EraseView.hh"

#include "../controllers/Clock.hh"

namespace Backdrop {

EraseView::EraseView(shared_ptr<sf::RenderWindow> _window) {
  window = _window;
}

void EraseView::render(shared_ptr<Clock::State> state) {
  window->clear();
}

}  // namespace Backdrop
