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

  auto map = std::make_shared<Map>(tileset, 20, 15);
  game.setMap(map);

  for (int y = 0; y < map->getHeight(); ++y) {
    for (int x = 0; x < map->getWidth(); ++x) {
      map->addTile(0, x, y);
    }
  }

  map->addTile(6, 6, 1);

  map->addTile(4, 3, 1);
  map->addTile(4, 3, 2);
  map->addTile(4, 3, 3);
  map->addTile(4, 4, 1);
  map->addTile(4, 4, 2);
  map->addTile(4, 4, 3);
  map->addTile(4, 5, 1);
  map->addTile(4, 5, 2);
  map->addTile(4, 5, 3);

  map->addTile(1, 10, 8);
  map->addTile(1, 10, 9);
  map->addTile(1, 11, 9);
  map->addTile(1, 12, 9);
  map->addTile(1, 13, 9);
  map->addTile(1, 10, 10);
  map->addTile(1, 12, 10);
  map->addTile(1, 9, 11);
  map->addTile(1, 10, 11);
  map->addTile(1, 11, 11);
  map->addTile(1, 12, 11);
  map->addTile(1, 12, 12);

  auto player = std::make_shared<Character>("jack", Object::Position{1, 1, Direction::Down});
  addKeyboardControl(game, player);

  game.addObject(std::make_shared<Object>(Object::Position{5, 3}));

  game.addObject(player);

  game.run();

  return 0;
}
