#include "core/EventListener.hh"
#include "core/Game.hh"
#include "core/Observer.hh"
#include "core/objects/Object.hh"

using namespace PonchoEngine;

using std::weak_ptr;

int main() {
  Game game;

  auto player = std::make_shared<Object>(Object::Position{1, 1});
  game.addObject(player);

  player->addEventListener(EventListener::Tick, [_player = weak_ptr<Object>(player)](shared_ptr<Observer::State> state) {
    auto player = _player.lock();
    if (!player) {
      return;
    }
    player->position.x += 1;
  });

  game.run();

  return 0;
}
