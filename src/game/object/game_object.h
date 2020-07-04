#ifndef RAYCASTER_GAME_OBJECT
#define RAYCASTER_GAME_OBJECT

#include "game_base_object.h"

class GameObject : public GameBaseObject
{
public:
  virtual ~GameObject() {}

  virtual void update() = 0;
  virtual void draw() = 0;
};

#endif
