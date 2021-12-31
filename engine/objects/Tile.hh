#ifndef TILE_HH
#define TILE_HH

#include <memory>
#include <string>

#include "../core/Tileset.hh"
#include "Object.hh"

using std::shared_ptr;
using std::string;

namespace Backdrop {

class Tile : public Object {
  Tileset tileset;
  int index;

 public:
  Tile(Object::Position _position, Tileset tileset, int index);
};

}  // namespace Backdrop

#endif
