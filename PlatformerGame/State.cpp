#include "State.h"

State::State(int* gamestate)
{
	this->gamestate = gamestate;
}

State::~State()
{
	delete gamestate;
}

bool State::IsIn(sf::Event::MouseButtonEvent e, MenuButton* mb)
{
	return mb->GetBounds()->getGlobalBounds().contains(sf::Vector2f((float)e.x, (float)e.y));
}
