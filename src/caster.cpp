#include "caster.h"
#include "constants.h"
#include <cmath>
#include <vector>

float dist(float ax, float ay, float bx, float by)
{
	return (std::sqrt(std::pow(bx - ax, 2) + std::pow(by - ay, 2)));
}

/*
 * radify
 * ======
 * Utility function to ensure number is within 0 and 2pi
 */
float radify(float& n)
{
	if (n < 0)
		n += 2 * PI;
	if (n > 2 * PI)
		n -= 2 * PI;

	return n;
}


Caster::Caster(const Level* l, const Player* p)
{
	level = l;
	player = p;
}

void Caster::update()
{

}

void Caster::draw()
{
	/*
	 * Variables
	 * =========
	 * int r: ray iterator
	 * int mx: map x of the player (array-wise)
	 * int my: map y of the player (array-wise)
	 * int mp: map position of the player (array-wise, position in the array)
	 * int dof: depth of field
	 * float rx: ray end x
	 * float ry: ray end y
	 * float ra: ray angle
	 * float xo: x-offset
	 * float yo: y-offset
	 * float distT: distance between ray and player
	 */
	int r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo;
	float distT;

	ra = player->getDirection() - DR * (FOV / 2); // First ray is has FOV / 2 degrees offset
	radify(ra); // Ensure ra is an allowed radian value

	for (r = 0; r < FOV; r++)
	{
		// Check horizontal lines
		dof = 0;
		float disH = 1000000, hx = player->getPos().x, hy = player->getPos().y;
		float aTan = -1 / std::tan(ra);

		if (ra > PI) // Looking Down
		{
			ry = (((int) player->getPos().y >> 6) << 6) - 0.0001; // Round to nearest 64
			rx = (player->getPos().y - ry) * aTan + player->getPos().x;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI) // Looking Up
		{
			ry = (((int) player->getPos().y >> 6) << 6) + 64; // Round to nearest 64
			rx = (player->getPos().y - ry) * aTan + player->getPos().x;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) // Looking straight horizontally
		{
			rx = player->getPos().x;
			ry = player->getPos().y;
			dof = level->getSize().x;
		}

		while (dof < level->getSize().x)
		{
			mx = (int) (rx) >> 6;
			my = (int) (ry) >> 6;
			mp = my * level->getSize().x + mx; // 8 is mapX

			if (mp < level->getSize().x * level->getSize().y && mp >= 0 && level->getRaw()[mp] == 1) // hit wall
			{
				hx = rx;
				hy = ry;
				disH = dist(player->getPos().x, player->getPos().y, hx, hy);
				dof = level->getSize().x;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		// Check vertical Lines
		dof = 0;
		float disV = 1000000, vx = player->getPos().x, vy = player->getPos().y;
		float nTan = -std::tan(ra);

		if (ra > P2 && ra < P3) // Looking Left
		{
			rx = (((int) player->getPos().x >> 6) << 6) - 0.0001; // Round to nearest 64
			ry = (player->getPos().x - rx) * nTan + player->getPos().y;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3) // Looking Right
		{
			rx = (((int) player->getPos().x >> 6) << 6) + 64; // Round to nearest 64
			ry = (player->getPos().x - rx) * nTan + player->getPos().y;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI) // Looking straight vertically
		{
			rx = player->getPos().x;
			ry = player->getPos().y;
			dof = level->getSize().x;
		}

		while (dof < level->getSize().x)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * level->getSize().x + mx; // 8 is mapX

			if (mp < level->getSize().x * level->getSize().y && mp >= 0 && level->getRaw()[mp] == 1) // hit wall
			{
				vx = rx;
				vy = ry;
				disV = dist(player->getPos().x, player->getPos().y, vx, vy);
				dof = level->getSize().x;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		// Find shortest ray
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			distT = disV;
			glColor3f(0.9, 0, 0);
		}
		else
		{
			rx = hx;
			ry = hy;
			distT = disH;
			glColor3f(0.7, 0, 0);
		}

		glLineWidth(1);
		glBegin(GL_LINES);
		glVertex2i(player->getPos().x, player->getPos().y);
		glVertex2i(rx, ry);
		glEnd();

		// Draw 3D Walls
		// Fix fisheye effect
		float ca = player->getDirection() - ra;
		radify(ca);
		distT = distT * std::cos(ca);

		// Draw the line
		float lineH = (64 * 320) / distT; // 64 is mapS
		if (lineH > 320)
			lineH = 320;
		float lineO = 160 - lineH / 2;

		glLineWidth(8);
		glBegin(GL_LINES);
		glVertex2i(r * 8 + 530, lineO);
		glVertex2i(r * 8 + 530, lineH + lineO);
		glEnd();

		ra += DR;
		radify(ra);
	}
}
