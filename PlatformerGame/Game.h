#pragma once

#include "Playing.h"
#include "Menu.h"

#include <iostream>

class Game
{
private:
	// Engine
	sf::RenderWindow* window;
	sf::Clock* clock;
	sf::Event* event;
	sf::Image* iconImage;

	Playing* playing;
	Menu* menu;

	int state = Gamestate::PLAYING;

	void InitGameEngine();
	void InitClasses();

	void Run();

	void DefaultEventHandler();
	void UpdateEvents();
	void UpdateProperties();
	void Update();

	void RenderProperties();
	void Render();

public:

	Game();
	~Game();

	int GetState();
};