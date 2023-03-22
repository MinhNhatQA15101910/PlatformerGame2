#include "Playing.h"

void Playing::InitClasses()
{
	levelManager = new LevelManager();
	player = new Player(200, 200, SCALE, SCALE);

	player->LoadLvlData(levelManager->GetCurrentLevel());
	pauseOverlay = new PauseOverlay(gamestate, &paused);
}

void Playing::CheckCloseToBorder()
{
	float playerX = player->GetHitbox()->getPosition().x;
	float diff = playerX - xLvlOffset;

	if (diff > rightBorder)
	{
		xLvlOffset += diff - rightBorder;
	}
	else if (diff < leftBorder)
	{
		xLvlOffset += diff - leftBorder;
	}

	if (xLvlOffset > maxLvlOffsetX)
	{
		xLvlOffset = maxLvlOffsetX;
	}
	else if (xLvlOffset < 0)
	{
		xLvlOffset = 0;
	}
}

void Playing::KeyReleased()
{
	switch (event->key.code)
	{
	case sf::Keyboard::A:
		player->SetLeft(false);
		break;
	case sf::Keyboard::D:
		player->SetRight(false);
		break;
	case sf::Keyboard::Space:
		player->SetJump(false);
		break;
	}
}

void Playing::KeyPressed()
{
	switch (event->key.code)
	{
	case sf::Keyboard::A:
		player->SetLeft(true);
		break;
	case sf::Keyboard::D:
		player->SetRight(true);
		break;
	case sf::Keyboard::Space:
		player->SetJump(true);
		break;
	case sf::Keyboard::Escape:
		paused = !paused;
		break;
	}
}

void Playing::MouseButtonPressed()
{
	if (paused)
	{
		pauseOverlay->MouseButtonPressed(event);
	}
}

void Playing::MouseButtonReleased()
{
	if (paused)
	{
		pauseOverlay->MouseButtonReleased(event);
	}
}

void Playing::MouseEntered()
{
}

void Playing::MouseLeft()
{
}

void Playing::MouseMoved()
{
	if (paused)
	{
		pauseOverlay->MouseMoved(event);
	}
}

Playing::Playing(int* gamestate)
	: State(gamestate)
{
	event = new sf::Event();

	InitClasses();
}

Playing::~Playing()
{
	State::~State();
	delete event;
	delete player;
	delete levelManager;
	delete pauseOverlay;
}

Player* Playing::GetPlayer()
{
	return player;
}

void Playing::UpdateProperties()
{
	if (!paused)
	{
		levelManager->UpdateProperties();
		player->UpdateProperties();
		CheckCloseToBorder();
	}
	else
	{
		pauseOverlay->UpdateProperties();
	}
}

void Playing::UpdateEvents(sf::Event* event)
{
	this->event = event;

	KeyEventHandler();
	MouseButtonEventHandler();
	MouseMoveEventHandler();
}

void Playing::Render(sf::RenderTarget* renderTarget)
{
	levelManager->Render(renderTarget, xLvlOffset);
	player->Render(renderTarget, xLvlOffset);

	if (paused)
	{
		sf::RectangleShape rectangle;
		rectangle.setFillColor(sf::Color(0, 0, 0, 150));
		rectangle.setPosition(0, 0);
		rectangle.setSize(sf::Vector2f(GAME_WIDTH, GAME_HEIGHT));
		renderTarget->draw(rectangle);

		pauseOverlay->Render(renderTarget);
	}
}

void Playing::KeyEventHandler()
{
	switch (event->type)
	{
	case sf::Event::KeyPressed:
		KeyPressed();
		break;
	case sf::Event::KeyReleased:
		KeyReleased();
		break;
	}
}

void Playing::MouseButtonEventHandler()
{
	switch (event->type)
	{
	case sf::Event::MouseButtonPressed:
		MouseButtonPressed();
		break;
	case sf::Event::MouseButtonReleased:
		MouseButtonReleased();
		break;
	}
}

void Playing::MouseMoveEventHandler()
{
	switch (event->type)
	{
	case sf::Event::MouseEntered:
		MouseEntered();
		break;
	case sf::Event::MouseLeft:
		MouseLeft();
		break;
	case sf::Event::MouseMoved:
		MouseMoved();
		break;
	}
}

void Playing::WindowFocusLost()
{
	if (event->type == sf::Event::LostFocus)
	{
		player->ResetDirBools();
	}
}
