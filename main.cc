#include "engine/engine.hh"

using namespace Backdrop;

using std::weak_ptr;

int main() {
  Game game;

  auto player = std::make_shared<Object>(Object::Position{1, 10});
  game.addObject(player);

  // player->addEventListener(EventListener::Tick, [_player = weak_ptr<Object>(player)](shared_ptr<Observer::State> state) {
  //   auto player = _player.lock();
  //   if (!player) {
  //     return;
  //   }
  //   player->position.x += 1;
  // });

  game.run();

  return 0;
}
