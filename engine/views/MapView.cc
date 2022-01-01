#include "MapView.hh"

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "../maps/Map.hh"
#include "../objects/Object.hh"
#include "../objects/Tile.hh"

using std::shared_ptr;

namespace Backdrop {

MapView::MapView(shared_ptr<sf::RenderWindow> _window, shared_ptr<Map>& map) : map{map} {
  window = _window;
}

void MapView::render(shared_ptr<Clock::State> state) {
  for (int y = 0; y < map->getHeight(); ++y) {
    for (int x = 0; x < map->getWidth(); ++x) {
      shared_ptr<Tile> tile = map->getTile(x, y);
      if (tile) {
        sf::Sprite sprite = tile->spriteManager->getSprite();
        sprite.setPosition(tile->position.getX() * 48, tile->position.getY() * 48);
        window->draw(sprite);
      }
    }
  }
}

}  // namespace Backdrop
