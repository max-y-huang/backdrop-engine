#ifndef CAMERA_VIEW_HH
#define CAMERA_VIEW_HH

#include <SFML/Graphics.hpp>
#include <memory>

#include "../controllers/Clock.hh"
#include "../objects/Object.hh"
#include "View.hh"

using std::shared_ptr;

namespace Backdrop {

class CameraView final : public View {
  void render(shared_ptr<Clock::State> state);
  shared_ptr<Object> boundedObject;

 public:
  CameraView(shared_ptr<sf::RenderWindow> _window);
  void bindToObject(shared_ptr<Object> object);
};

}  // namespace Backdrop

#endif
