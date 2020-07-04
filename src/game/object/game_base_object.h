#ifndef RAYCASTER_GAME_BASE_OBJECT
#define RAYCASTER_GAME_BASE_OBJECT

class GameBaseObject
{
public:
  virtual ~GameBaseObject() {}

  virtual void update() = 0;
  virtual void draw() = 0;
};

#endif
