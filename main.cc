#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "engine/engine.hh"

using namespace Backdrop;

using std::cout;
using std::endl;
using std::pair;
using std::shared_ptr;
using std::vector;
using std::weak_ptr;

void addKeyboardControl(Game& game, shared_ptr<Character> character) {
  bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;
  auto _character = weak_ptr<Character>(character);
  character->onActionKey([_character, &moveUp, &moveDown, &moveLeft, &moveRight](shared_ptr<Keyboard::State> state) {
    auto character = _character.lock();
    if (!character) {
      return;
    }
    // Handle move.
    if (state->active) {
      if (state->action == Action::MoveUp) {
        moveUp = true;
      }
      if (state->action == Action::MoveDown) {
        moveDown = true;
      }
      if (state->action == Action::MoveLeft) {
        moveLeft = true;
      }
      if (state->action == Action::MoveRight) {
        moveRight = true;
      }
    }
    // Handle dash.
    if (state->action == Action::Dash) {
      character->setDash(state->active);
    }
  });

  character->onTick([_character, &moveUp, &moveDown, &moveLeft, &moveRight](shared_ptr<Clock::State> state) {
    auto character = _character.lock();
    if (!character) {
      return;
    }
    if (moveUp && moveDown) {
      moveUp = false;
      moveDown = false;
    }
    if (moveLeft && moveRight) {
      moveLeft = false;
      moveRight = false;
    }
    if (moveUp) {
      if (moveLeft) {
        character->moveLeft(sqrt(2) / 2);
        character->moveUp(sqrt(2) / 2);
      } else if (moveRight) {
        character->moveRight(sqrt(2) / 2);
        character->moveUp(sqrt(2) / 2);
      } else {
        character->moveUp();
      }
    } else if (moveDown) {
      if (moveLeft) {
        character->moveLeft(sqrt(2) / 2);
        character->moveDown(sqrt(2) / 2);
      } else if (moveRight) {
        character->moveRight(sqrt(2) / 2);
        character->moveDown(sqrt(2) / 2);
      } else {
        character->moveDown();
      }
    } else if (moveLeft) {
      character->moveLeft();
    } else if (moveRight) {
      character->moveRight();
    }
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
  });
}

int main() {
  vector<pair<int, int>> lava = {
      {4, 2},
      {5, 2},
      {6, 2},
      {6, 3},
  };
  vector<pair<int, int>> floor = {
      {0, 1},
      {1, 1},
      {2, 1},
      {3, 1},
      {4, 1},
      {5, 1},
      {6, 1},
      {7, 1},
      {0, 2},
      {1, 2},
      {3, 2},
      {7, 2},
      {0, 3},
      {1, 3},
      {7, 3},
      {0, 4},
      {1, 4},
      {3, 4},
      {5, 4},
      {6, 4},
      {7, 4},
      {0, 5},
      {5, 5},
      {6, 5},
      {7, 5},
      {0, 6},
      {1, 6},
      {2, 6},
      {3, 6},
      {5, 6},
      {6, 6},
      {7, 6},
      {0, 7},
      {1, 7},
      {2, 7},
      {3, 7},
      {4, 7},
      {5, 7},
      {6, 7},
      {7, 7},
      {10, 8},
      {10, 9},
      {11, 9},
      {12, 9},
      {13, 9},
      {10, 10},
      {12, 10},
      {9, 11},
      {10, 11},
      {11, 11},
      {12, 11},
      {12, 12},
  };

  Game game;
  Tileset tileset{"ground_a"};

  auto map = std::make_shared<Map>(game, tileset, 20, 15);
  game.setMap(map);

  for (int y = 0; y < map->getHeight(); ++y) {
    for (int x = 0; x < map->getWidth(); ++x) {
      bool temp = false;
      for (auto c : floor) {
        if (c.first == x && c.second == y) {
          map->addTile(1, x, y);
          temp = true;
        }
      }
      for (auto c : lava) {
        if (c.first == x && c.second == y) {
          map->addTile(2, x, y);
          temp = true;
        }
      }
      if (!temp) {
        map->addTile(0, x, y);
      }
    }
  }

  auto player = std::make_shared<Character>("jack", Position{1, 1, Direction::Down});
  addKeyboardControl(game, player);
  game.addObject(player);

  game.run();

  return 0;
}
