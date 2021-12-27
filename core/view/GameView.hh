#ifndef GAME_VIEW_HH
#define GAME_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "../Clock.hh"
#include "View.hh"

namespace PonchoEngine {

class GameView final : public View {
  void render(shared_ptr<Clock::State> state);

 public:
  GameView(shared_ptr<sf::RenderWindow> _window);
};

}  // namespace PonchoEngine

#endif
