#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "controllers/Clock.hh"
#include "objects/Object.hh"
#include "views/EraseView.hh"
#include "views/GameView.hh"
#include "views/RefreshView.hh"

using std::shared_ptr;
using std::vector;

namespace PonchoEngine {

class Game {
  shared_ptr<sf::RenderWindow> window;  // Leaks 5,419 bytes.
  shared_ptr<Clock> clock;
  shared_ptr<EraseView> eraseView;
  shared_ptr<RefreshView> refreshView;
  shared_ptr<GameView> gameView;
  vector<shared_ptr<Object>> objects;
  void handleClose();

 public:
  Game();
  ~Game();
  void run();
  void addObject(shared_ptr<Object> object);
};

}  // namespace PonchoEngine

#endif
