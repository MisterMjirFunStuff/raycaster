#ifndef RAYCAST_LEVEL
#define RAYCAST_LEVEL

#include <vector>
#include <string>
#include "game.h"

struct LevelSize
{
	int x;
	int y;
};

class Level : public GameObject
{
public:
	const static int tileSize = 64;

	Level();
	int load(std::string fpath);
	int load(const std::vector<int>&);
	void update();
	void draw();
	std::vector<int> getRaw() const { return raw;  }
	LevelSize getSize() const { return size; }
private:
	std::vector<int> raw;
	LevelSize size;
	int spawnX, spawnY;
};

#endif
