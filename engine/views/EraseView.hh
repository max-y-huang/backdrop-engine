#ifndef ERASE_VIEW_HH
#define ERASE_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "View.hh"

namespace Backdrop {

class EraseView final : public View {
  void render(shared_ptr<Clock::State> state);

 public:
  EraseView(shared_ptr<sf::RenderWindow> _window);
};

}  // namespace Backdrop

#endif
