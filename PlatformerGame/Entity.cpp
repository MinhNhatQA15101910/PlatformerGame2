#include "Entity.h"

void Entity::InitHitbox(float x, float y, float width, float height)
{
	hitbox = new sf::RectangleShape();
	hitbox->setPosition(x, y);
	hitbox->setSize(sf::Vector2f(width, height));
}

void Entity::DrawHitbox(sf::RenderTarget* renderTarget)
{
	hitbox->setFillColor(sf::Color(255, 192, 203));
	renderTarget->draw(*hitbox);
}

Entity::Entity(float x, float y, float scaleX, float scaleY)
{
	this->x = x;
	this->y = y;
	this->scaleX = scaleX;
	this->scaleY = scaleY;

	InitHitbox(0, 0, 0, 0);
}

Entity::~Entity()
{
	delete hitbox;
}

sf::RectangleShape* Entity::GetHitbox()
{
	return hitbox;
}
