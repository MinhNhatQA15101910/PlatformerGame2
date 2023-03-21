#include "Menu.h"

Menu::Menu(int* gamestate)
	: State(gamestate)
{
	event = new sf::Event();

	LoadButtons();
	LoadBackground();
}

Menu::~Menu()
{
	State::~State();
	delete event;
	delete backgroundSprite;
	delete backgroundTexture;
	for (int i = 0; i < 3; i++)
	{
		delete buttons[i];
	}
}

void Menu::UpdateProperties()
{
	for (MenuButton* mb : buttons)
	{
		mb->UpdateProperties();
	}
}

void Menu::UpdateEvents(sf::Event* event)
{
	this->event = event;

	KeyEventHandler();
	MouseButtonEventHandler();
	MouseMoveEventHandler();
}

void Menu::Render(sf::RenderTarget* renderTarget)
{
	backgroundSprite->setPosition(menuX, menuY);
	backgroundSprite->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*backgroundSprite);

	for (MenuButton* mb : buttons)
	{
		mb->Render(renderTarget);
	}
}

void Menu::KeyEventHandler()
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

void Menu::MouseButtonEventHandler()
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

void Menu::MouseMoveEventHandler()
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

void Menu::LoadButtons()
{
	buttons[0] = new MenuButton((int)(GAME_WIDTH / 2), (int)(150 * SCALE), 0, gamestate, Constants::Gamestate::PLAYING);
	buttons[1] = new MenuButton((int)(GAME_WIDTH / 2), (int)(220 * SCALE), 1, gamestate, Constants::Gamestate::OPTIONS);
	buttons[2] = new MenuButton((int)(GAME_WIDTH / 2), (int)(290 * SCALE), 2, gamestate, Constants::Gamestate::QUIT);
}

void Menu::LoadBackground()
{
	backgroundTexture = LoadSave::GetTextureAtlas(MENU_BACKGROUND);

	backgroundSprite = new sf::Sprite();
	backgroundSprite->setTexture(*backgroundTexture);

	menuWidth = (backgroundTexture->getSize().x * SCALE);
	menuHeight = (backgroundTexture->getSize().y * SCALE);
	menuX = GAME_WIDTH / 2 - menuWidth / 2;
	menuY = (45 * SCALE);
}

void Menu::ResetButtons()
{
	for (MenuButton* mb : buttons)
	{
		mb->ResetBools();
	}
}

void Menu::KeyReleased()
{
}

void Menu::KeyPressed()
{
	if (event->key.code == sf::Keyboard::Enter)
	{
		*gamestate = Constants::Gamestate::PLAYING;
	}
}

void Menu::MouseButtonPressed()
{
	for (MenuButton* mb : buttons)
	{
		if (IsIn(event->mouseButton, mb))
		{
			mb->SetMousePressed(true);
		}
	}
}

void Menu::MouseButtonReleased()
{
	for (MenuButton* mb : buttons)
	{
		if (IsIn(event->mouseButton, mb))
		{
			if (mb->IsMousePressed())
			{
				mb->ApplyGamestate();
			}
			break;
		}
	}

	ResetButtons();
}

void Menu::MouseEntered()
{
}

void Menu::MouseLeft()
{
}

void Menu::MouseMoved()
{
	for (MenuButton* mb : buttons)
	{
		mb->SetMouseOver(false);
	}

	for (MenuButton* mb : buttons)
	{
		if (IsIn(event->mouseButton, mb))
		{
			mb->SetMouseOver(true);
			break;
		}
	}
}
