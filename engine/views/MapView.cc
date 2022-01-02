#include "MapView.hh"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../controllers/Clock.hh"
#include "../maps/Map.hh"

using std::shared_ptr;

namespace Backdrop {

MapView::MapView(shared_ptr<sf::RenderWindow> _window, shared_ptr<Map>& map) : map{map} {
  window = _window;
}

void MapView::render(shared_ptr<Clock::State> state) {
  for (int y = 0; y < map->getHeight(); ++y) {
    for (int x = 0; x < map->getWidth(); ++x) {
      for (int layer = 0; layer < 3; ++layer) {
        if (map->getTile(x, y, layer)) {
          sf::Sprite sprite = map->getTile(x, y, layer)->spriteManager->getSprite();
          sprite.setPosition(x * 48, y * 48);
          window->draw(sprite);
        }
      }
    }
  }
}

}  // namespace Backdrop
