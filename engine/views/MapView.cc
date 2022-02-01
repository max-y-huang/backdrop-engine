#include "MapView.hh"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "../controllers/Clock.hh"
#include "../maps/Map.hh"

using std::shared_ptr;

namespace Backdrop {

MapView::MapView(shared_ptr<sf::RenderWindow> _window, shared_ptr<Map>& map, bool overhead) : map{map}, overhead{overhead} {
  window = _window;
}

void MapView::render(shared_ptr<Clock::State> state) {
  sf::Sprite sprite = overhead ? map->spriteManager->getOverheadSprite() : map->spriteManager->getSprite();
  window->draw(sprite);
}

}  // namespace Backdrop
