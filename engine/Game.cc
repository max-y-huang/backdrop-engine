#include "Game.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "controllers/Clock.hh"
#include "controllers/Keyboard.hh"
#include "core/FrameRate.hh"
#include "core/Observer.hh"
#include "managers/CollisionManager.hh"
#include "maps/Map.hh"
#include "objects/Character.hh"
#include "objects/Object.hh"
#include "views/EraseView.hh"
#include "views/FrameRateView.hh"
#include "views/MapView.hh"
#include "views/ObjectView.hh"
#include "views/RefreshView.hh"

#define FPS 1000  // Set unreasonably high to test maximum FPS.
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 720
#define WINDOW_TITLE "Game window"

namespace Backdrop {

Game::Game() {
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE);
  setIcon();
  drawSplashScreen();
  clock = std::make_shared<Clock>(window, FPS);
  keyboard = std::make_shared<Keyboard>();
  eraseView = std::make_shared<EraseView>(window);
  refreshView = std::make_shared<RefreshView>(window);
  frameRateView = std::make_shared<FrameRateView>(window);
  mapView = std::make_shared<MapView>(window, map);
  objectView = std::make_shared<ObjectView>(window, objects);
  collisionManager = std::make_shared<CollisionManager>(objects);

  clock->attach(FrameRate::getInstance(), 300);
  clock->attach(keyboard, 200);
  clock->attach(eraseView, 99);
  clock->attach(refreshView, 0);
  clock->attach(frameRateView, 1);
  clock->attach(mapView, 51);
  clock->attach(objectView, 50);
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

void Game::setIcon() {
  sf::Image image;
  image.loadFromFile("assets/images/system/icon.png");
  window->setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void Game::drawSplashScreen() {
  sf::Image logoImage;
  logoImage.loadFromFile("assets/images/system/splashScreen.png");
  sf::Image image;
  image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color::Black);
  int logoX = (window->getSize().x - logoImage.getSize().x) / 2;
  int logoY = (window->getSize().y - logoImage.getSize().y) / 2;
  image.copy(logoImage, logoX, logoY);
  sf::Texture texture;
  texture.loadFromImage(image);
  sf::Sprite sprite{texture};
  window->clear();
  window->draw(sprite);
  window->display();
}

void Game::setMap(shared_ptr<Map> _map) {
  map = _map;
}

void Game::addObject(shared_ptr<Object> object) {
  objects.push_back(object);
  clock->attach(object, 100);
  clock->attach(object->spriteManager, 200);
  keyboard->attach(object, 100);
  object->attach(collisionManager, 200);
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
