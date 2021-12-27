#ifndef VIEW_HH
#define VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>
#include <utility>

#include "../Clock.hh"
#include "../Observer.hh"

using std::pair;
using std::priority_queue;
using std::shared_ptr;

namespace PonchoEngine {

class View : public Observer {
 protected:
  shared_ptr<sf::RenderWindow> window;
  void onNotify(shared_ptr<Observer::State> state);
  virtual void render(shared_ptr<Clock::State> state) = 0;

 public:
  virtual ~View() = default;
};

}  // namespace PonchoEngine

#endif