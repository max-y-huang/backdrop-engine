#ifndef DEBUGGER_HH
#define DEBUGGER_HH

#include <memory>

using std::shared_ptr;

namespace Backdrop {

class Debugger final {
  static shared_ptr<Debugger> instance;
  double frameRate = 0;

 public:
  Debugger() {}
  Debugger(Debugger &other) = delete;              // Disallow instances of this class.
  void operator=(const Debugger &other) = delete;  // Disallow instances of this class.
  static shared_ptr<Debugger> getInstance();
  bool isDebugMode();
};

}  // namespace Backdrop

#endif
