#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "Clock.hh"
#include "view/EraseView.hh"
#include "view/GameView.hh"

using std::shared_ptr;

namespace PonchoEngine {

class Game {
  shared_ptr<sf::RenderWindow> window;  // Leaks 5,419 bytes.
  shared_ptr<Clock> clock;
  shared_ptr<EraseView> eraseView;
  shared_ptr<GameView> gameView;
  void handleClose();

 public:
  Game();
  void run();
};

}  // namespace PonchoEngine

#endif
