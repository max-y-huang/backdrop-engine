#include "Keyboard.hh"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <fstream>
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
    actionBindings[pair.value()] = ConfigMap::Action::getAction(pair.key());
  }
}

void Keyboard::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    notifyActions();
    keysPressed.clear();
  }
}

void Keyboard::notifyActions() {
  for (auto actionPair : actionBindings) {
    bool active = keysPressed[actionPair.first];
    notifyObservers(std::make_shared<Keyboard::State>(actionPair.second, active));
  }
}

void Keyboard::update() {
  for (auto actionPair : actionBindings) {
    // Handle keyboard keys.
    if (actionPair.first < 100) {
      auto key = static_cast<sf::Keyboard::Key>(actionPair.first);
      if (sf::Keyboard::isKeyPressed(key)) {
        keysPressed[actionPair.first] = true;
      }
    }
    // Handle mouse buttons.
    else {
      auto button = static_cast<sf::Mouse::Button>(actionPair.first - 100);
      if (sf::Mouse::isButtonPressed(button)) {
        keysPressed[actionPair.first] = true;
      }
    }
  }
}

}  // namespace Backdrop
