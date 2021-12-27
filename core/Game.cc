#include "Game.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "Clock.hh"
#include "Observer.hh"
#include "view/EraseView.hh"
#include "view/GameView.hh"

#define FPS 2
#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Temp game"

namespace PonchoEngine {

Game::Game() {
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
  clock = std::make_shared<Clock>(FPS);
  eraseView = std::make_shared<EraseView>(window);
  gameView = std::make_shared<GameView>(window);
  clock->attach(eraseView, 1);
  clock->attach(gameView, 0);
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

}  // namespace PonchoEngine
