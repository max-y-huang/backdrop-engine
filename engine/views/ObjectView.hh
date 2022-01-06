#ifndef OBJECT_VIEW_HH
#define OBJECT_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "../controllers/Clock.hh"
#include "../objects/Object.hh"
#include "View.hh"

using std::vector;

namespace Backdrop {

class ObjectView final : public View {
  sf::Texture shadowTexture;
  vector<shared_ptr<Object>>& objects;
  void render(shared_ptr<Clock::State> state);

 public:
  ObjectView(shared_ptr<sf::RenderWindow> _window, vector<shared_ptr<Object>>& objects);
};

}  // namespace Backdrop

#endif
