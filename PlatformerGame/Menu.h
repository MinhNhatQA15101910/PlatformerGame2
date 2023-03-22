#pragma once

#include "Statemethods.h"
#include "EventHandler.h"
#include "Constants.h"
#include "State.h"
#include "MenuButton.h"
#include "HelpMethods.h"

#include <iostream>

class Menu : public State, public Statemethods, public EventHandler
{
private:
	sf::Event* event;

	MenuButton* buttons[3];
	sf::Texture* backgroundTexture, * backgroundTexturePink;
	sf::Sprite* backgroundSprite, * backgroundSpritePink;
	float menuX, menuY, menuWidth, menuHeight;

	void LoadButtons();
	void LoadBackground();

	void ResetButtons();

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
	Menu(int* gamestate);
	~Menu();

	void UpdateProperties();
	void UpdateEvents(sf::Event* event);

	void Render(sf::RenderTarget* renderTarget);

	void KeyEventHandler();
	void MouseButtonEventHandler();
	void MouseMoveEventHandler();
};

