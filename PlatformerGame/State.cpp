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
	return 
		(e.x > mb->GetBounds()->getPosition().x) &&
		(e.y > mb->GetBounds()->getPosition().y) &&
		(e.x < mb->GetBounds()->getPosition().x + mb->GetBounds()->getSize().x) && 
		(e.y < mb->GetBounds()->getPosition().y + mb->GetBounds()->getSize().y);
}
