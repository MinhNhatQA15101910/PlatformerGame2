#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

class Entity
{
protected:
	float x, y;
	float width, height;
	sf::RectangleShape* hitbox;

	void InitHitbox(float x, float y, float width, float height);

	void DrawHitbox(sf::RenderTarget* renderTarget, int xLvlOffset);

public:
	Entity(float x, float y, float width, float height);
	~Entity();

	sf::RectangleShape* GetHitbox();
};

