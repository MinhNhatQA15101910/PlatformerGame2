#pragma once

#include "Player.h"
#include "LevelManager.h"

#include <iostream>

class Game
{
private:
	// Engine
	sf::RenderWindow* window;
	sf::Clock* clock;
	sf::Event* event;
	sf::Image* iconImage;

	const int FPS_SET = 120;
	const int UPS_SET = 200;

	Player* player;
	LevelManager* levelManager;

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
};