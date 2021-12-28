#include "core/EventListener.hh"
#include "core/Game.hh"
#include "core/Observer.hh"
#include "core/object/Object.hh"

using namespace PonchoEngine;

int main() {
  Game game;

  auto player = std::make_shared<Object>(Object::Position{1, 1});
  game.addObject(player);
  player->addEventListener(EventListener::Tick, [player](shared_ptr<Observer::State> state) {
    player->position.x += 1;
  });

  game.run();

  return 0;
}
