#ifndef MAP_VIEW_HH
#define MAP_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "../maps/Map.hh"
#include "View.hh"

using std::shared_ptr;

namespace Backdrop {

class MapView final : public View {
  shared_ptr<Map>& map;
  bool overhead;
  void render(shared_ptr<Clock::State> state);

 public:
  MapView(shared_ptr<sf::RenderWindow> _window, shared_ptr<Map>& map, bool overhead);
};

}  // namespace Backdrop

#endif
