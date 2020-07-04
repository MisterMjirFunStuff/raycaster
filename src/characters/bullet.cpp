#include "bullet.h"
#include <iostream>

Bullet::Bullet(const Level* l, float x, float y, float dx, float dy)
{
  this->x = x;
  this->y = y;
  this->dx = dx;
  this->dy = dy;
  level = l;
  active = true;
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
  x += dx;
  y += dy;

  int mx = (int) (x) >> 6;
	int my = (int) (y) >> 6;
	int mp = my * level->getSize().x + mx;

  if (mp < level->getSize().x * level->getSize().y && mp >= 0)
  {
    if (level->getRaw()[mp] == 1)
      active = false;
  }
}

void Bullet::draw()
{
	glColor3f(1, 1, 0);
	glPointSize(4);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}
