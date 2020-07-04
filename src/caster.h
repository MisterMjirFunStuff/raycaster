#ifndef RAYCAST_CASTER
#define RAYCAST_CASTER

#include "game.h"
#include "constants.h"
#include "level.h"
#include "player.h"

class Caster : public GameObject
{
public:
	static const int FOV = 60;

	Caster(const Level* l, const Player* p);
	void update();
	void draw();
private:
	const Level* level;
	const Player* player;
};

#endif
