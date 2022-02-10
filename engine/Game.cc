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
#include "views/CameraView.hh"
#include "views/EraseView.hh"
#include "views/FrameRateView.hh"
#include "views/MapView.hh"
#include "views/ObjectView.hh"
#include "views/RefreshView.hh"

#define FPS 1000  // Set unreasonably high to test maximum FPS.
#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 960
#define WINDOW_TITLE "Game window"

namespace Backdrop {

Game::Game() {
  // window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE, sf::Style::Fullscreen);
  window = std::make_shared<sf::RenderWindow>(sf::VideoMode{WINDOW_WIDTH, WINDOW_HEIGHT}, WINDOW_TITLE);
  setIcon();
  drawSplashScreen();
  Clock::makeInstance(window, FPS);  // Needs to be made with arguments.
  eraseView = std::make_shared<EraseView>(window);
  refreshView = std::make_shared<RefreshView>(window);
  frameRateView = std::make_shared<FrameRateView>(window);
  cameraView = std::make_shared<CameraView>(window);
  mapView = std::make_shared<MapView>(window, map, false);
  overheadMapView = std::make_shared<MapView>(window, map, true);
  objectView = std::make_shared<ObjectView>(window, objects);
  collisionManager = std::make_shared<CollisionManager>(objects);

  Clock::getInstance()->attach(FrameRate::getInstance(), 300);
  Clock::getInstance()->attach(Keyboard::getInstance(), 200);
  Clock::getInstance()->attach(eraseView, 99);
  Clock::getInstance()->attach(refreshView, 0);
  Clock::getInstance()->attach(cameraView, 98);
  Clock::getInstance()->attach(frameRateView, 2);
  Clock::getInstance()->attach(mapView, 52);
  Clock::getInstance()->attach(overheadMapView, 50);
  Clock::getInstance()->attach(objectView, 51);
}

Game::~Game() {
}

void Game::run() {
  while (window->isOpen()) {
    handleClose();
    Keyboard::getInstance()->update();
    Clock::getInstance()->update();
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
  map->loadTiles();
}

void Game::addObject(shared_ptr<Object> object) {
  objects.push_back(object);
  Clock::getInstance()->attach(object, 100);
  Clock::getInstance()->attach(object->spriteManager, 200);
  Keyboard::getInstance()->attach(object, 100);
  object->attach(collisionManager, 200);
}

void Game::removeObject(shared_ptr<Object> object) {
  for (size_t i = 0; i < objects.size(); ++i) {
    if (object == objects[i]) {
      Clock::getInstance()->detach(object);
      Clock::getInstance()->detach(object->spriteManager);
      Keyboard::getInstance()->detach(object);
      objects.erase(objects.begin() + i);
      --i;
    }
  }
}

void Game::bindCameraToObject(shared_ptr<Object> object) {
  cameraView->bindToObject(object);
}

}  // namespace Backdrop
