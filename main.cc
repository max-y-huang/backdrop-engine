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
      if (state->action == Keyboard::Action::MoveUp) {
        character->moveUp();
      }
      if (state->action == Keyboard::Action::MoveDown) {
        character->moveDown();
      }
      if (state->action == Keyboard::Action::MoveLeft) {
        character->moveLeft();
      }
      if (state->action == Keyboard::Action::MoveRight) {
        character->moveRight();
      }
    }
    // Handle dash.
    if (state->action == Keyboard::Action::Dash) {
      character->setDash(state->active);
    }
  });
}

int main() {
  Game game;

  auto male = std::make_shared<Character>(Object::Position{1, 1, Direction::Down}, "assets/images/topdowns/male_walk.png");
  addKeyboardControl(game, male);

  auto female = std::make_shared<Character>(Object::Position{2, 2, Direction::Down}, "assets/images/topdowns/female_walk.png");
  addKeyboardControl(game, female);

  game.addObject(male);
  game.addObject(female);

  game.run();

  return 0;
}
