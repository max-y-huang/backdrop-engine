#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "engine/engine.hh"
#include "lib/nlohmann/json.hpp"

using namespace Backdrop;

using nlohmann::json;
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
      if (state->action == "moveUp") {
        moveUp = true;
      }
      if (state->action == "moveDown") {
        moveDown = true;
      }
      if (state->action == "moveLeft") {
        moveLeft = true;
      }
      if (state->action == "moveRight") {
        moveRight = true;
      }
    }
    // Handle dash.
    if (state->action == "dash") {
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
  Game game;
  Tileset tileset{};

  std::ifstream file{"config/maps.json"};
  json data;
  file >> data;

  auto map = std::make_shared<Map>(game, tileset, data);
  game.setMap(map);

  auto player = std::make_shared<Character>("jack", Position{1, 1, Direction::Down});
  addKeyboardControl(game, player);
  game.addObject(player);

  game.run();

  return 0;
}
