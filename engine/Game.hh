#ifndef GAME_HH
#define GAME_HH

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "managers/CollisionManager.hh"
#include "maps/Map.hh"
#include "objects/Object.hh"
#include "views/CameraView.hh"
#include "views/EraseView.hh"
#include "views/FrameRateView.hh"
#include "views/MapView.hh"
#include "views/ObjectView.hh"
#include "views/RefreshView.hh"

using std::shared_ptr;
using std::vector;

namespace Backdrop {

class Game final {
  shared_ptr<sf::RenderWindow> window;  // Leaks 5,475 + 56 bytes from graphics driver(?).
  shared_ptr<EraseView> eraseView;
  shared_ptr<RefreshView> refreshView;
  shared_ptr<CameraView> cameraView;
  shared_ptr<FrameRateView> frameRateView;
  shared_ptr<MapView> mapView;
  shared_ptr<MapView> overheadMapView;
  shared_ptr<ObjectView> objectView;
  shared_ptr<CollisionManager> collisionManager;
  shared_ptr<Map> map;
  vector<shared_ptr<Object>> objects;
  void handleClose();
  void setIcon();
  void drawSplashScreen();

 public:
  Game();
  ~Game();
  void run();
  void setMap(shared_ptr<Map> _map);
  void addObject(shared_ptr<Object> object);
  void removeObject(shared_ptr<Object> object);
  void bindCameraToObject(shared_ptr<Object> object);
};

}  // namespace Backdrop

#endif
