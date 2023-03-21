#pragma once

#include <SFML/Graphics.hpp>
#include "MenuButton.h"

class State
{
protected: 
	int* gamestate;

public:
	State(int* gamestate);
	~State();

	bool IsIn(sf::Event::MouseButtonEvent e, MenuButton* mb);
};

