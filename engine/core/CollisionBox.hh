#ifndef COLLISION_BOX_HH
#define COLLISION_BOX_HH

#include <iostream>
#include <memory>

#include "Position.hh"

using std::shared_ptr;

namespace Backdrop {

class CollisionBox final {
 public:
  struct InitializerList final {
    float x, y, width, height;
  };

 private:
  Position &position;
  // float x;
  // float y;
  // float width;
  // float height;

 public:
  float x;
  float y;
  float width;
  float height;
  float getGlobalX() {
    return position.getX() + x;
  }
  float getGlobalY() {
    return position.getY() + y;
  }
  CollisionBox(Position &position, float x, float y, float width, float height) : position{position}, x{x}, y{y}, width{width}, height{height} {}
  bool touching(shared_ptr<CollisionBox> other);
};

}  // namespace Backdrop

#endif
