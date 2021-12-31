#ifndef TILESET_HH
#define TILESET_HH

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

namespace Backdrop {

class Tileset {
  sf::Texture texture;
  int width;
  int height;
  bool autoTiles;
  int animationFrames;
  void initializeParameters(string name);

 public:
  Tileset(string name);
};

}  // namespace Backdrop

#endif
