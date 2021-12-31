#include <iostream>
#include <memory>
#include <string>

#include "engine/engine.hh"

using namespace Backdrop;

using std::cout;
using std::endl;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

void addKeyboardControl(Game& game, shared_ptr<Character> character) {
  auto _character = weak_ptr<Character>(character);
  character->onActionKey([&game, _character](shared_ptr<Keyboard::State> state) {
    auto character = _character.lock();
    if (!character) {
      return;
    }
    // Handle move.
    if (state->active) {
      if (state->action == Action::MoveUp) {
        character->moveUp();
      }
      if (state->action == Action::MoveDown) {
        character->moveDown();
      }
      if (state->action == Action::MoveLeft) {
        character->moveLeft();
      }
      if (state->action == Action::MoveRight) {
        character->moveRight();
      }
    }
    // Handle dash.
    if (state->action == Action::Dash) {
      character->setDash(state->active);
    }
  });
}

int main() {
  Game game;
  Tileset tileset{"ground"};

  auto jack = std::make_shared<Character>(Object::Position{1, 1, Direction::Down}, "jack");
  addKeyboardControl(game, jack);

  auto jill = std::make_shared<Character>(Object::Position{2, 2, Direction::Down}, "jill");
  addKeyboardControl(game, jill);

  auto bush = std::make_shared<Tile>(Object::Position{1, 1}, tileset, 12);

  game.addObject(bush);

  game.addObject(jack);
  game.addObject(jill);

  game.run();

  return 0;
}
