#include "Keyboard.hh"

#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <memory>

#include "../../lib/nlohmann/json.hpp"
#include "../configMaps.hh"
#include "../core/Observer.hh"
#include "Clock.hh"

using nlohmann::json;
using std::shared_ptr;

namespace Backdrop {

Keyboard::Keyboard() {
  createActionMap();
}

void Keyboard::createActionMap() {
  std::ifstream file{"config/controls.json"};
  json data;
  file >> data;
  for (auto pair : data.items()) {
    actionMap[pair.value()] = ConfigMap::KeyboardAction::getAction(pair.key());
  }
}

shared_ptr<Observer::State> Keyboard::getState() {
  return std::make_shared<Keyboard::State>(Keyboard::Action::MoveUp);
}

void Keyboard::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    for (auto actionPair : actionMap) {
      if (keysPressed[actionPair.first]) {
        notifyObservers(std::make_shared<Keyboard::State>(actionPair.second));
      }
    }
    keysPressed.clear();
  }
}

void Keyboard::update() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    keysPressed["UP"] = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    keysPressed["DOWN"] = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    keysPressed["LEFT"] = true;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    keysPressed["RIGHT"] = true;
  }
}

}  // namespace Backdrop
