#include "CollisionManager.hh"

#include <cmath>
#include <memory>

#include "../core/Observer.hh"
#include "../objects/Object.hh"

using std::shared_ptr;

namespace Backdrop {

CollisionManager::CollisionManager(vector<shared_ptr<Object>>& objects) : objects{objects} {}

bool CollisionManager::touching(shared_ptr<Object> a, shared_ptr<Object> b) {
  float diffX = a->position.getX() - b->position.getX();
  float diffY = a->position.getY() - b->position.getY();
  diffX = (diffX < 0) ? -diffX : diffX;
  diffY = (diffY < 0) ? -diffY : diffY;
  return a != b && diffX <= 48 && diffY <= 48;  // Return false if a and b are the same object.
}

void CollisionManager::onNotify(shared_ptr<Observer::State> state) {
  auto objectCollideState = std::dynamic_pointer_cast<Object::CollideState>(state);
  if (objectCollideState) {
    for (auto object : objects) {
      if (touching(objectCollideState->self, object)) {
        objectCollideState->self->position = objectCollideState->prevPosition;
      }
    }
  }
}

}  // namespace Backdrop
