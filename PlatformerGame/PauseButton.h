#pragma once

#include "SFML/Graphics.hpp"

class PauseButton
{
protected:
	float x, y, width, height;
	sf::RectangleShape* bounds;

	void CreateBounds();

public:
	PauseButton(float x, float y, float width, float height);
	~PauseButton();

	float GetX();
	float GetY();
	float GetWidth();
	float GetHeight();
	sf::RectangleShape* GetBounds();

	void SetX(float x);
	void SetY(float y);
	void SetWidth(float width);
	void SetHeight(float height);
	void SetBounds(sf::RectangleShape* bounds);
};

