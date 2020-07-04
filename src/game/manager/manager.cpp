#include "manager.h"

Manager::Manager()
{

}

Manager::~Manager()
{
  clearObjects();
}

void Manager::update()
{
  for (auto obj: objects)
    obj->update();
}

void Manager::draw()
{
  for (auto obj: objects)
    obj->draw();
}

void Manager::clearObjects()
{
  for (auto obj: objects)
    delete obj;
  objects.clear();
}
