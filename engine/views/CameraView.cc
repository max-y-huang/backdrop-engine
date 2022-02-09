#include "CameraView.hh"

#include <memory>

#include "../controllers/Clock.hh"
#include "../objects/Object.hh"

using std::shared_ptr;

namespace Backdrop {

CameraView::CameraView(shared_ptr<sf::RenderWindow> _window) {
  window = _window;
}

void CameraView::bindToObject(shared_ptr<Object> object) {
  boundedObject = object;
}

void CameraView::render(shared_ptr<Clock::State> state) {
  float screenHeight = 960;
  float screenWidth = screenHeight * window->getSize().x / window->getSize().y;
  sf::View view(sf::FloatRect{0, 0, screenWidth, screenHeight});
  if (boundedObject) {
    float objectX = boundedObject->position.getX();
    float objectY = boundedObject->position.getY();
    view.move(objectX - screenWidth / 2 + 24, objectY - screenHeight / 2 + 24);
  }
  window->setView(view);
}

}  // namespace Backdrop
