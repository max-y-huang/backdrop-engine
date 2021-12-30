#include "Game.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "controllers/Clock.hh"
#include "controllers/Keyboard.hh"
#include "core/FrameRate.hh"
#include "core/Observer.hh"
#include "objects/Character.hh"
#include "objects/Object.hh"
#include "views/EraseView.hh"
#include "views/FrameRateView.hh"
#include "views/GameView.hh"
#include "views/RefreshView.hh"

#define FPS 1000  // Set unreasonably high to test maximum FPS.
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Game window"

namespace Backdrop {

Game::Game() {
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE);
  clock = std::make_shared<Clock>(FPS);
  keyboard = std::make_shared<Keyboard>();
  eraseView = std::make_shared<EraseView>(window);
  refreshView = std::make_shared<RefreshView>(window);
  frameRateView = std::make_shared<FrameRateView>(window);
  gameView = std::make_shared<GameView>(window, objects);
  clock->attach(FrameRate::getInstance(), 300);
  clock->attach(keyboard, 200);
  clock->attach(eraseView, 99);
  clock->attach(refreshView, 0);
  clock->attach(frameRateView, 1);
  clock->attach(gameView, 50);
}

Game::~Game() {
}

void Game::run() {
  while (window->isOpen()) {
    handleClose();
    keyboard->update();
    clock->update();
  }
}

void Game::handleClose() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      window->close();
    }
  }
}

void Game::addObject(shared_ptr<Object> object) {
  objects.push_back(object);
  clock->attach(object, 100);
  clock->attach(object->spriteManager, 200);
  keyboard->attach(object, 100);
}

void Game::removeObject(shared_ptr<Object> object) {
  for (size_t i = 0; i < objects.size(); ++i) {
    if (object == objects[i]) {
      clock->detach(object);
      clock->detach(object->spriteManager);
      keyboard->detach(object);
      objects.erase(objects.begin() + i);
      --i;
    }
  }
}

}  // namespace Backdrop
