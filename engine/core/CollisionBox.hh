#ifndef COLLISION_BOX_HH
#define COLLISION_BOX_HH

#include <memory>

#include "Position.hh"

using std::shared_ptr;

namespace Backdrop {

class CollisionBox {
  // Position &parent;
};

class RectCollisionBox : public CollisionBox {
  bool touchingRect(shared_ptr<RectCollisionBox> other) {
    //
  }
  bool touchingCircle(shared_ptr<CircleCollisionBox> other) {
    //
  }
  bool touching(shared_ptr<CollisionBox> other) {
    auto rect = std::dynamic_pointer_cast<RectCollisionBox>(other);
    auto circle = std::dynamic_pointer_cast<CircleCollisionBox>(other);
    if (rect) {
      return touchingRect(rect);
    }
    if (circle) {
      return touchingCircle(circle);
    }
    return false;
  }
};

class CircleCollisionBox : public CollisionBox {
  bool touching(shared_ptr<CollisionBox> other) {
    return false;
  }
};

}  // namespace Backdrop

#endif
