#ifndef FRAME_RATE_HH
#define FRAME_RATE_HH

#include <memory>

#include "Observer.hh"

using std::shared_ptr;

namespace Backdrop {

class FrameRate final : public Observer {
  static shared_ptr<FrameRate> instance;
  double frameRate = 0;
  void onNotify(shared_ptr<Observer::State> state);

 public:
  FrameRate() {}
  FrameRate(FrameRate &other) = delete;             // Disallow instances of this class.
  void operator=(const FrameRate &other) = delete;  // Disallow instances of this class.
  static shared_ptr<FrameRate> getInstance();
  double getFrameRate();
};

}  // namespace Backdrop

#endif
