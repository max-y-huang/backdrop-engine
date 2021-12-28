#ifndef GAME_VIEW_HH
#define GAME_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../Clock.hh"
#include "../object/Object.hh"
#include "View.hh"

using std::vector;

namespace PonchoEngine {

class GameView final : public View {
  vector<shared_ptr<Object>>& objects;
  void render(shared_ptr<Clock::State> state);

 public:
  GameView(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Object>>& objects);
};

}  // namespace PonchoEngine

#endif
