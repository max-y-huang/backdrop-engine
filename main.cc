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

  auto map = std::make_shared<Map>(tileset, 8, 6);
  game.setMap(map);
  map->addTile(1, 0, 0);
  map->addTile(1, 0, 1);
  map->addTile(1, 1, 1);

  auto jack = std::make_shared<Character>("jack", Object::Position{1, 1, Direction::Down});
  addKeyboardControl(game, jack);

  auto jill = std::make_shared<Character>("jill", Object::Position{2, 2, Direction::Down});
  addKeyboardControl(game, jill);

  game.addObject(jack);
  game.addObject(jill);

  game.run();

  return 0;
}
