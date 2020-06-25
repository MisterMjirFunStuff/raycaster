#ifndef RAYCAST_LEVEL
#define RAYCAST_LEVEL

#include <vector>
#include <string>

struct LevelSize
{
	int x;
	int y;
};

class Level
{
public:
	const static int tileSize = 64;

	Level();
	int load(std::string fpath);
	int load(const std::vector<int>&);
	void draw();
	std::vector<int> getRaw() const { return raw;  }
	LevelSize getSize() const { return size; }
private:
	std::vector<int> raw;
	LevelSize size;
	int spawnX, spawnY;
};

#endif