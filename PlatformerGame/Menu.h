#pragma once

#include "Statemethods.h"
#include "EventHandler.h"
#include "Constants.h"
#include "State.h"

#include <iostream>

class Menu : public State, public Statemethods, public EventHandler 
{
private:
	sf::Event* event;

	sf::Font* font;
	sf::Text* text;

	// Key handler
	void KeyReleased();
	void KeyPressed();

	// Mouse button handler
	void MouseButtonPressed();
	void MouseButtonReleased();

	// Mouse move handler
	void MouseEntered();
	void MouseLeft();
	void MouseMoved();

public:
	Menu(int* state);
	~Menu();

	void UpdateProperties();
	void UpdateEvents(sf::Event* event);

	void Render(sf::RenderTarget* renderTarget);

	void KeyEventHandler();
	void MouseButtonEventHandler();
	void MouseMoveEventHandler();
};

