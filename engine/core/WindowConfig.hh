#ifndef WINDOW_CONFIG_HH
#define WINDOW_CONFIG_HH

#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

namespace Backdrop {

class WindowConfig final {
  static shared_ptr<WindowConfig> instance;
  unsigned int width;
  unsigned int height;
  string title;
  double fps;
  bool fullscreen;

 public:
  WindowConfig();
  WindowConfig(WindowConfig &other) = delete;          // Disallow instances of this class.
  void operator=(const WindowConfig &other) = delete;  // Disallow instances of this class.
  static shared_ptr<WindowConfig> getInstance();
  unsigned int getWidth();
  unsigned int getHeight();
  string getTitle();
  double getFPS();
  bool getFullscreen();
};

}  // namespace Backdrop

#endif
