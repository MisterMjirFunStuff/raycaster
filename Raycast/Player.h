#ifndef RAYCAST_PLAYER
#define RAYCAST_PLAYER

struct PlayerPosition
{
	float x;
	float y;
};

class Player
{
public:
	Player();
	Player(float x, float y);
	void draw();
	PlayerPosition moveX(float d);
	PlayerPosition moveY(float d);
	float turn(float a);

	PlayerPosition getPos() const { return pos; }
	PlayerPosition getDeltaPos() const { return deltaPos; }
	float getDirection() const { return direction; }
private:
	PlayerPosition pos, deltaPos;
	float direction;
};

#endif