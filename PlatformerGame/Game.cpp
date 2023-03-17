#include "Game.h"

Game::Game()
{
	InitGameEngine();
	InitClasses();

	Run();
}

Game::~Game()
{
	delete event;
	delete clock;
	delete iconImage;
	delete window;

	delete player;
	delete levelManager;
}

void Game::InitGameEngine()
{
	event = new sf::Event();
	clock = new sf::Clock();

	iconImage = LoadSave::GetImageAtlas(ICON_IMAGE);

	window = new sf::RenderWindow(sf::VideoMode((int)GAME_WIDTH, (int)GAME_HEIGHT), WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar);
	window->setIcon(iconImage->getSize().x, iconImage->getSize().y, iconImage->getPixelsPtr());
	window->setFramerateLimit(FRAMERATE_LIMIT);
}

void Game::InitClasses()
{
	player = new Player(200, 200, SCALE, SCALE);
	levelManager = new LevelManager();
}

void Game::Run()
{
	double timePerFrame = (1000000000.0 / FPS_SET);
	double timePerUpdate = 1000000000.0 / UPS_SET;

	sf::Time previousTime = clock->getElapsedTime();

	int frames = 0;
	int updates = 0;
	sf::Time lastCheck = clock->getElapsedTime();

	double deltaU = 0.f;
	double deltaF = 0.f;

	while (window->isOpen())
	{
		sf::Time currentTime = clock->getElapsedTime();

		deltaU += (currentTime.asMicroseconds() * 1000 - previousTime.asMicroseconds() * 1000) / timePerUpdate;
		deltaF += (currentTime.asMicroseconds() * 1000 - previousTime.asMicroseconds() * 1000) / timePerFrame;

		if (deltaU >= 1)
		{
			Update();
			updates++;
			deltaU--;
		}

		if (deltaF >= 1)
		{
			Render();
			frames++;
			deltaF--;
		}

		if (clock->getElapsedTime().asMilliseconds() - lastCheck.asMilliseconds() >= 1000)
		{
			lastCheck = clock->getElapsedTime();
			std::cout << "FPS: " + std::to_string(frames) + " | UPS: " + std::to_string(updates) + "\n";
			frames = 0;
			updates = 0;
		}
	}
}

void Game::DefaultEventHandler()
{
	if (event->type == sf::Event::Closed)
		window->close();
	else if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::Escape)
		window->close();
}

void Game::UpdateEvents()
{
	while (window->pollEvent(*event))
	{
		DefaultEventHandler();
		player->UpdateEvents(event);
	}
}

void Game::UpdateProperties()
{
	levelManager->UpdateProperties();
	player->UpdateProperties();
}

void Game::Update()
{
	UpdateEvents();
	UpdateProperties();
}

void Game::RenderProperties()
{
	levelManager->Render(window);
	player->Render(window);
}

void Game::Render()
{
	// Clear window
	window->clear();

	RenderProperties();

	// Display window
	window->display();
}
