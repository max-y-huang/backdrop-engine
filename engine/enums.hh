#ifndef ENUMS_HH
#define ENUMS_HH

namespace Backdrop {

enum Direction {
  Up,
  Down,
  Left,
  Right,
  UpLeft,
  UpRight,
  DownLeft,
  DownRight,
};

enum Action {
  _None,
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Dash,
  Attack,
};

}  // namespace Backdrop

#endif
