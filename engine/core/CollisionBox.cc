#include "CollisionBox.hh"

namespace Backdrop {

bool CollisionBox::touching(shared_ptr<CollisionBox> other) {
  float x1 = getGlobalX();
  float y1 = getGlobalY();
  float w1 = width;
  float h1 = height;
  float x2 = other->getGlobalX();
  float y2 = other->getGlobalY();
  float w2 = other->width;
  float h2 = other->height;
  bool overlapX = (w1 + w2 > x2 + w2 - x1) && (w1 + w2 > x1 + w1 - x2);
  bool overlapY = (h1 + h2 > y2 + h2 - y1) && (h1 + h2 > y1 + h1 - y2);
  return overlapX && overlapY;
}

}  // namespace Backdrop
