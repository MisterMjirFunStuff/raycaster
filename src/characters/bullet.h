#ifndef RAYCASTER_BULLET
#define RAYCASTER_BULLET

#include "game.h"
#include "level.h"

class Bullet : public GameObject
{
public:
  Bullet(const Level*, float x, float y, float dx, float dy);
  ~Bullet();
  void update();
  void draw();
  bool isActive() {return active;}
private:
  float x, y, dx, dy;
  bool active;
  const Level* level;
};

#endif
