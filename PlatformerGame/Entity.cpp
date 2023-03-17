#include "Entity.h"

Entity::Entity(float x, float y, float scaleX, float scaleY)
{
	this->x = x;
	this->y = y;
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

Entity::~Entity()
{
}
