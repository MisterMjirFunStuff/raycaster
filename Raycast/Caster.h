#ifndef RAYCAST_CASTER
#define RAYCAST_CASTER

#include "Constants.h"
#include "Level.h"
#include "Player.h"

class Caster
{
public:
	static const int FOV = 60;

	Caster(const Level* l, const Player* p);
	void draw();
private:
	const Level* level;
	const Player* player;
};

#endif