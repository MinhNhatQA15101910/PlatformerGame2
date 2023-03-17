#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "EventHandler.h"

class Entity
{
protected:
	float x, y;
	float scaleX, scaleY;

public:
	Entity(float x, float y, float scaleX, float scaleY);
	~Entity();
};

