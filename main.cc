#include <iostream>
#include <memory>

#include "engine/engine.hh"

using namespace Backdrop;

using std::cout;
using std::endl;
using std::weak_ptr;

int main() {
  Game game;

  auto player = std::make_shared<Object>(Object::Position{1, 10});
  auto _player = weak_ptr<Object>(player);
  game.addObject(player);

  player->onActionKey([_player](shared_ptr<Keyboard::State> state) {
    auto player = _player.lock();
    if (!player) {
      return;
    }
    if (state->action == Keyboard::Action::MoveUp) {
      player->position.moveUp();
    }
    if (state->action == Keyboard::Action::MoveDown) {
      player->position.moveDown();
    }
    if (state->action == Keyboard::Action::MoveLeft) {
      player->position.moveLeft();
    }
    if (state->action == Keyboard::Action::MoveRight) {
      player->position.moveRight();
    }
  });

  game.run();

  return 0;
}
