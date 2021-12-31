#ifndef TILESET_HH
#define TILESET_HH

#include <SFML/Graphics.hpp>
#include <string>

using std::string;

namespace Backdrop {

class Tileset final {
  string id;
  sf::Texture texture;
  int width;
  int height;
  bool autoTiles;
  int animationFrames;
  void initializeParameters(string id);

 public:
  Tileset(string id);
  string getId();
  int getWidth();
  int getHeight();
  bool isAutoTiles();
  int getAnimationFrames();
};

}  // namespace Backdrop

#endif
