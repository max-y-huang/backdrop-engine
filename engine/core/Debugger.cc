#include "Debugger.hh"

#include <memory>

using std::shared_ptr;

namespace Backdrop {

shared_ptr<Debugger> Debugger::instance = nullptr;

shared_ptr<Debugger> Debugger::getInstance() {
  if (!instance) {
    instance = std::make_shared<Debugger>();
  }
  return instance;
}

bool Debugger::isDebugMode() {
  return true;
}

}  // namespace Backdrop
