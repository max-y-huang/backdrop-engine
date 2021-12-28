#ifndef REFRESH_VIEW_HH
#define REFRESH_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "View.hh"

namespace PonchoEngine {

class RefreshView final : public View {
  void render(shared_ptr<Clock::State> state);

 public:
  RefreshView(shared_ptr<sf::RenderWindow> _window);
};

}  // namespace PonchoEngine

#endif
