#pragma once

#include "Player.h"
#include "LevelManager.h"
#include "Statemethods.h"
#include "State.h"
#include "EventHandler.h"

class Playing : public State, public Statemethods, public EventHandler
{
private:
	sf::Event* event;

	Player* player;
	LevelManager* levelManager;

	void InitClasses();

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
	Playing(int* state);
	~Playing();

	Player* GetPlayer();

	void UpdateProperties();
	void UpdateEvents(sf::Event* event);

	void Render(sf::RenderTarget* renderTarget);

	void KeyEventHandler();
	void MouseButtonEventHandler();
	void MouseMoveEventHandler();
	void WindowFocusLost();
};

