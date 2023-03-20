#include "Menu.h"

Menu::Menu(int* state)
	: State(state)
{
	event = new sf::Event();

	font = new sf::Font();
	if (!font->loadFromFile("fonts\\Dosis-Light.ttf"))
	{
		std::cout << "Cannot load font\n";
	}

	text = new sf::Text();
	text->setFont(*font);
	text->setString("MENU");
	text->setCharacterSize(16);
}

Menu::~Menu()
{
	delete event;
	delete text;
	delete font;
}

void Menu::UpdateProperties()
{
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
	text->setFillColor(sf::Color::White);
	text->setPosition(GAME_WIDTH / 2, 200);

	renderTarget->draw(*text);
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

void Menu::KeyReleased()
{
}

void Menu::KeyPressed()
{
	if (event->key.code == sf::Keyboard::Enter)
	{
		*state = Gamestate::PLAYING;
	}
}

void Menu::MouseButtonPressed()
{
}

void Menu::MouseButtonReleased()
{
}

void Menu::MouseEntered()
{
}

void Menu::MouseLeft()
{
}

void Menu::MouseMoved()
{
}
