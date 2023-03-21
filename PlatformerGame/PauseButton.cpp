#include "PauseButton.h"

void PauseButton::CreateBounds()
{
	bounds = new sf::RectangleShape();
	bounds->setPosition(x, y);
	bounds->setSize(sf::Vector2f(width, height));

}

PauseButton::PauseButton(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	CreateBounds();
}

PauseButton::~PauseButton()
{
	delete bounds;
}

float PauseButton::GetX()
{
	return x;
}

float PauseButton::GetY()
{
	return y;
}

float PauseButton::GetWidth()
{
	return width;
}

float PauseButton::GetHeight()
{
	return height;
}

sf::RectangleShape* PauseButton::GetBounds()
{
	return bounds;
}

void PauseButton::SetX(float x)
{
	this->x = x;
}

void PauseButton::SetY(float y)
{
	this->y = y;
}

void PauseButton::SetWidth(float width)
{
	this->width = width;
}

void PauseButton::SetHeight(float height)
{
	this->height = height;
}

void PauseButton::SetBounds(sf::RectangleShape* bounds)
{
	this->bounds = bounds;
}
