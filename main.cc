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

  auto male = std::make_shared<Character>(Object::Position{1, 1, Direction::Down}, "male");
  addKeyboardControl(game, male);

  auto female = std::make_shared<Character>(Object::Position{2, 2, Direction::Down}, "female");
  addKeyboardControl(game, female);

  game.addObject(male);
  game.addObject(female);

  game.run();

  return 0;
}
