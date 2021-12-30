#ifndef FRAME_RATE_VIEW_HH
#define FRAME_RATE_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "View.hh"

namespace Backdrop {

class FrameRateView final : public View {
  double frameRate = 0;
  void onNotify(shared_ptr<Observer::State> state);
  void render(shared_ptr<Clock::State> state);

 public:
  FrameRateView(shared_ptr<sf::RenderWindow> _window);
};

}  // namespace Backdrop

#endif
