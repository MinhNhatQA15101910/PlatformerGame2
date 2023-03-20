#pragma once

#include <SFML/Graphics.hpp>

class Statemethods
{
public:
	virtual void UpdateProperties() = 0;
	virtual void UpdateEvents(sf::Event* event) = 0;
	virtual void Render(sf::RenderTarget* renderTarget) = 0;
};