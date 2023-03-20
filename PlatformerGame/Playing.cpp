#include "Playing.h"

void Playing::InitClasses()
{
	levelManager = new LevelManager();
	player = new Player(200, 200, SCALE, SCALE);

	player->LoadLvlData(levelManager->GetCurrentLevel()->GetLvlData());
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
	case sf::Keyboard::Backspace:
		*state = Gamestate::MENU;
		break;
	}
}

void Playing::MouseButtonPressed()
{
	if (event->mouseButton.button == sf::Mouse::Left)
	{
		player->SetAttacking(true);
	}
}

void Playing::MouseButtonReleased()
{
}

void Playing::MouseEntered()
{
}

void Playing::MouseLeft()
{
}

void Playing::MouseMoved()
{
}

Playing::Playing(int* state)
	: State(state)
{
	event = new sf::Event();

	InitClasses();
}

Playing::~Playing()
{
	delete event;
	delete player;
	delete levelManager;
}

Player* Playing::GetPlayer()
{
	return player;
}

void Playing::UpdateProperties()
{
	levelManager->UpdateProperties();
	player->UpdateProperties();
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
	levelManager->Render(renderTarget);
	player->Render(renderTarget);
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