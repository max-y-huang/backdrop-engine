#include "CameraView.hh"

#include <SFML/Graphics.hpp>
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
  if (boundedObject) {
    float screenHeight = 960;
    float screenWidth = screenHeight * window->getSize().x / window->getSize().y;
    float objectX = boundedObject->position.getX();
    float objectY = boundedObject->position.getY();
    sf::View view{sf::FloatRect{0, 0, screenWidth, screenHeight}};
    view.setCenter(objectX + 24, objectY + 24);
    window->setView(view);
  }
}

}  // namespace Backdrop
