#include "MenuButton.h"

void MenuButton::LoadSprites()
{
	texture = LoadSave::GetTextureAtlas(MENU_BUTTONS);
	for (int i = 0; i < spritesLength; i++)
	{
		sprites[i] = new sf::Sprite();
		sprites[i]->setTexture(*texture);
		sprites[i]->setTextureRect(sf::IntRect(
			/* rectLeft = */   i * B_WIDTH_DEFAULT,
			/* rectTop = */    rowIndex * B_HEIGHT_DEFAULT,
			/* rectWidth = */  B_WIDTH_DEFAULT,
			/* rectHeigth = */ B_HEIGHT_DEFAULT
		));
	}
}

void MenuButton::InitBounds()
{
	bounds = new sf::RectangleShape();
	bounds->setPosition((float)(xPos - xOffsetCenter), (float)yPos);
	bounds->setSize(sf::Vector2f(B_WIDTH, B_HEIGHT));
}

MenuButton::MenuButton(int xPos, int yPos, int rowIndex, int* gamestate, int gamestateValue)
{
	this->xPos = xPos;
	this->yPos = yPos;
	this->rowIndex = rowIndex;
	this->gamestate = gamestate;
	this->gamestateValue = gamestateValue;
	LoadSprites();
	InitBounds();
}

MenuButton::~MenuButton()
{
	delete gamestate;
	delete texture;
	delete bounds;
	for (int i = 0; i < spritesLength; i++)
	{
		delete sprites[i];
	}
}

bool MenuButton::IsMouseOver()
{
	return mouseOver;
}

bool MenuButton::IsMousePressed()
{
	return mousePressed;
}

sf::RectangleShape* MenuButton::GetBounds()
{
	return bounds;
}

void MenuButton::SetMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

void MenuButton::SetMousePressed(bool mousePressed)
{
	this->mousePressed = mousePressed;
}

void MenuButton::ApplyGamestate()
{
	*gamestate = gamestateValue;
}

void MenuButton::ResetBools()
{
	mouseOver = false;
	mousePressed = false;
}

void MenuButton::UpdateProperties()
{
	index = 0;
	if (mouseOver)
	{
		index = 1;
	}
	if (mousePressed)
	{
		index = 2;
	}
}

void MenuButton::Render(sf::RenderTarget* renderTarget)
{
	sprites[index]->setPosition((float)(xPos - xOffsetCenter), (float)yPos);
	sprites[index]->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*sprites[index]);
}
