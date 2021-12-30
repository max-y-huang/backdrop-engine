#include "FrameRate.hh"

#include <memory>

#include "../controllers/Clock.hh"

using std::shared_ptr;

namespace Backdrop {

shared_ptr<FrameRate> FrameRate::instance = nullptr;

shared_ptr<FrameRate> FrameRate::getInstance() {
  if (!instance) {
    instance = std::make_shared<FrameRate>();
  }
  return instance;
}

void FrameRate::onNotify(shared_ptr<Observer::State> state) {
  auto clockState = std::dynamic_pointer_cast<Clock::State>(state);
  if (clockState) {
    frameRate = 1000000.0 / clockState->tickLength;
  }
}

double FrameRate::getFrameRate() {
  return frameRate;
}

}  // namespace Backdrop
