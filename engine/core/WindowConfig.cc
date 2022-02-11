#include "WindowConfig.hh"

#include <fstream>
#include <memory>
#include <string>

#include "../../lib/nlohmann/json.hpp"

using nlohmann::json;
using std::shared_ptr;
using std::string;

namespace Backdrop {

shared_ptr<WindowConfig> WindowConfig::instance = nullptr;

WindowConfig::WindowConfig() {
  std::ifstream file{"config/window.json"};
  json data;
  file >> data;
  width = int(data["width"]);
  height = int(data["height"]);
  title = string(data["title"]);
  fps = double(data["fps"]);
  fullscreen = bool(data["fullscreen"]);
}

shared_ptr<WindowConfig> WindowConfig::getInstance() {
  if (!instance) {
    instance = std::make_shared<WindowConfig>();
  }
  return instance;
}

unsigned int WindowConfig::getWidth() {
  return width;
}
unsigned int WindowConfig::getHeight() {
  return height;
}
string WindowConfig::getTitle() {
  return title;
}
double WindowConfig::getFPS() {
  return fps;
}
bool WindowConfig::getFullscreen() {
  return fullscreen;
}

}  // namespace Backdrop
