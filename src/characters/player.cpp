#include "player.h"
#include <cmath>
#include "constants.h"
#include "bullet.h"

const float Player::maxVelocity = 1;

Player::Player(const Level* l)
{
	pos.x = pos.y = 0;
	deltaPos.x = std::cos(direction) * 5;
	deltaPos.y = std::sin(direction) * 5;
	direction = 0;
	velocity = 0;

	oldPos = pos;

	level = l;
}

Player::Player(float x, float y, const Level* l)
{
	pos.x = x;
	pos.y = y;
	deltaPos.x = std::cos(direction) * 5;
	deltaPos.y = std::sin(direction) * 5;
	direction = 0;
	velocity = 0;

	oldPos = pos;

	level = l;
}

void Player::update()
{
	if (Game::getInputs().up || Game::getInputs().down)
	{
		if (Game::getInputs().up)
		{
			if (velocity < maxVelocity)
				velocity += 0.1;
		}
		else
		{
			if (velocity > -maxVelocity)
				velocity -= 0.1;
		}
	}
	else
	{
		velocity /= 2;
	}

	move(deltaPos.x * velocity, deltaPos.y * velocity);


	if (Game::getInputs().left)
		turn(-0.05);

	if (Game::getInputs().right)
		turn(0.05);

	// Bullet handling stuff
	if (Game::getInputs().shoot)
		objects.push_back(new Bullet(level, pos.x, pos.y, deltaPos.x, deltaPos.y));

		for (int i = objects.size() - 1; i >= 0; i--)
	  {
	    objects.at(i)->update();
	    if (!dynamic_cast<Bullet*>(objects.at(i))->isActive())
	    {
	      delete objects.at(i);
	      objects.erase(objects.begin() + i);
	    }
	  }
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

	Manager::draw();
}


const int paddingSize = 8;
PlayerPosition Player::move(float dx, float dy)
{
	moveX(dx);
	moveY(dy);

	// Check collision
	int mx = (int) (pos.x) >> 6;
	int my = (int) (pos.y) >> 6;
	int mp = my * level->getSize().x + mx;

	if (mp < level->getSize().x * level->getSize().y && mp >= 0)
	{
		if (level->getRaw()[mp] == 1)
		{
			pos = oldPos;
			velocity /= -2;
		}
		else
		{
			// Right wall padding
			if (mp % level->getSize().x < level->getSize().x)
			{
				if (level->getRaw()[mp + 1] == 1)
				{
					if (pos.x - mx * 64 > 64 - paddingSize)
					{
						pos = oldPos;
						velocity /= -2;
					}
				}
			}
			// Left wall padding
			if (mp % level->getSize().x > 0)
			{
				if (level->getRaw()[mp - 1] == 1)
				{
					if (pos.x - mx * 64 < paddingSize)
					{
						pos = oldPos;
						velocity /= -2;
					}
				}
			}
			// Top wall padding
			if (mp / level->getSize().x > 0)
			{
				if (level->getRaw()[mp - level->getSize().x] == 1)
				{
					if (pos.y - my * 64 < paddingSize)
					{
						pos = oldPos;
						velocity /= -2;
					}
				}
			}
			// Bottom wall padding
			if (mp / level->getSize().x + 1 < level->getSize().y)
			{
				if (level->getRaw()[mp + level->getSize().x] == 1)
				{
					if (pos.y - my * 64 > 64 - paddingSize)
					{
						pos = oldPos;
						velocity /= -2;
					}
				}
			}
		}
	}

	oldPos = pos;

	return pos;
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
