#include "RefreshView.hh"

#include "../controllers/Clock.hh"

namespace PonchoEngine {

RefreshView::RefreshView(shared_ptr<sf::RenderWindow> _window) {
  window = _window;
}

void RefreshView::render(shared_ptr<Clock::State> state) {
  window->display();
}

}  // namespace PonchoEngine
