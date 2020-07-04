#ifndef RAYCAST_PLAYER
#define RAYCAST_PLAYER

#include "game.h"
#include "level.h"

struct PlayerPosition
{
	float x;
	float y;
};

class Player : public GameObject, public Manager
{
public:
	Player(const Level*);
	Player(float x, float y, const Level*);
	void update();
	void draw();
	PlayerPosition move(float dx, float dy);
	float turn(float a);

	PlayerPosition getPos() const { return pos; }
	PlayerPosition getDeltaPos() const { return deltaPos; }
	float getDirection() const { return direction; }
private:
	PlayerPosition pos, deltaPos, oldPos; // pos = current, delta = movement w/ turn, old = previous pos
	static const float maxVelocity;
	float velocity;
	float direction;
	const Level* level;

	PlayerPosition moveX(float d);
	PlayerPosition moveY(float d);
};

#endif
