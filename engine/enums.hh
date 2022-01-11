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
  NoAction,
  MoveUp,
  MoveDown,
  MoveLeft,
  MoveRight,
  Dash,
  Attack,
};

enum AutoTileType {
  NoAutoTile,
  Normal,
  Wall,
};

}  // namespace Backdrop

#endif
