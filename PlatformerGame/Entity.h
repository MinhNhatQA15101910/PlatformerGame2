#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Entity
{
protected:
	float x, y;
	float scaleX, scaleY;
	sf::RectangleShape* hitbox;

	void InitHitbox(float x, float y, float width, float height);

	void DrawHitbox(sf::RenderTarget* renderTarget);

public:
	Entity(float x, float y, float scaleX, float scaleY);
	~Entity();
};

