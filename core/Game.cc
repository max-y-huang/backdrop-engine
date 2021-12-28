#include "Game.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "Observer.hh"
#include "controllers/Clock.hh"
#include "views/EraseView.hh"
#include "views/GameView.hh"
#include "views/RefreshView.hh"

#define FPS 2
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Temp game"

namespace PonchoEngine {

Game::Game() {
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE);
  clock = std::make_shared<Clock>(FPS);
  eraseView = std::make_shared<EraseView>(window);
  refreshView = std::make_shared<RefreshView>(window);
  gameView = std::make_shared<GameView>(window, objects);
  clock->attach(eraseView, 99);
  clock->attach(refreshView, 0);
  clock->attach(gameView, 50);
}

Game::~Game() {
  // for (auto object : objects) {
  //   object.reset();
  // }
}

void Game::run() {
  while (window->isOpen()) {
    handleClose();
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
}

}  // namespace PonchoEngine
