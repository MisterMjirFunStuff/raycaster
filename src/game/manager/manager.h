#ifndef RAYCASTER_MANAGER
#define RAYCASTER_MANAGER

#include <vector>
#include "game_base_object.h"
#include "game_object.h"

class Manager : public GameBaseObject
{
public:
  Manager();
  ~Manager();

  virtual void update();
  virtual void draw();

  std::vector<GameObject*> objects;
protected:
  virtual void clearObjects();
};

#endif
