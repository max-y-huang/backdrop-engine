#ifndef COLLISION_MANAGER_HH
#define COLLISION_MANAGER_HH

#include <memory>

#include "../core/Observer.hh"
#include "../objects/Object.hh"

using std::shared_ptr;

namespace Backdrop {

class CollisionManager : public Observer, public Observer::Subject {
  vector<shared_ptr<Object>>& objects;
  bool touching(shared_ptr<Object> a, shared_ptr<Object> b);
  void onNotify(shared_ptr<Observer::State> state);

 public:
  CollisionManager(vector<shared_ptr<Object>>& objects);
};

}  // namespace Backdrop

#endif
