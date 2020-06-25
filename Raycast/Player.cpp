#include "Player.h"
#include <cmath>
#include "Constants.h"

Player::Player()
{
	pos.x = pos.y = 0;
	deltaPos.x = std::cos(direction) * 5;
	deltaPos.y = std::sin(direction) * 5;
	direction = 0;
}

Player::Player(float x, float y)
{
	pos.x = x;
	pos.y = y;
	deltaPos.x = std::cos(direction) * 5;
	deltaPos.y = std::sin(direction) * 5;
	direction = 0;
}

void Player::draw()
{
	// Draw player
	glColor3f(1, 1, 0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(pos.x, pos.y);
	glEnd();

	// Draw direction indicator
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(pos.x, pos.y);
	glVertex2i(pos.x + deltaPos.x * 5, pos.y + deltaPos.y * 5);
	glEnd();
}

PlayerPosition Player::moveX(float d)
{
	pos.x += d;
	return pos;
}

PlayerPosition Player::moveY(float d)
{
	pos.y += d;
	return pos;
}


float Player::turn(float a)
{
	direction += a;

	if (direction < 0)
		direction += 2 * PI;

	if (direction > 2 * PI)
		direction -= 2 * PI;

	deltaPos.x = std::cos(direction) * 5;
	deltaPos.y = std::sin(direction) * 5;

	return direction;
}