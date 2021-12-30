#include "Keyboard.hh"

#include <SFML/Window/Keyboard.hpp>
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
    auto key = static_cast<sf::Keyboard::Key>(pair.value());
    auto action = pair.key();
    actionBindings[key] = ConfigMap::KeyboardAction::getAction(action);
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
    bool active = keysPressed.count(actionPair.first) ? keysPressed[actionPair.first] : false;
    notifyObservers(std::make_shared<Keyboard::State>(actionPair.second, active));
  }
}

void Keyboard::update() {
  for (int i = 0; i < sf::Keyboard::Key::KeyCount; ++i) {  // sf::Keyboard::Key::KeyCount comes after all key codes.
    auto key = static_cast<sf::Keyboard::Key>(i);
    if (sf::Keyboard::isKeyPressed(key)) {
      keysPressed[key] = true;
    }
  }
}

}  // namespace Backdrop
