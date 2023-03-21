#include "UrmButton.h"

void UrmButton::LoadSprites()
{
	texture = LoadSave::GetTextureAtlas(URM_BUTTONS);
	for (int i = 0; i < 3; i++)
	{
		sprites[i] = new sf::Sprite();
		sprites[i]->setTexture(*texture);
		sprites[i]->setTextureRect(sf::IntRect(
			i * URM_DEFAULT_SIZE, 
			rowIndex * URM_DEFAULT_SIZE, 
			URM_DEFAULT_SIZE, 
			URM_DEFAULT_SIZE
		));
	}
}

UrmButton::UrmButton(float x, float y, float width, float height, int rowIndex)
	: PauseButton(x, y, width, height)
{
	this->rowIndex = rowIndex;
	LoadSprites();
}

UrmButton::~UrmButton()
{
	delete texture;
	for (int i = 0; i < 3; i++)
	{
		delete sprites[i];
	}
}

bool UrmButton::IsMouseOver()
{
	return mouseOver;
}

bool UrmButton::IsMousePressed()
{
	return mousePressed;
}

void UrmButton::SetMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

void UrmButton::SetMousePressed(bool mousePressed)
{
	this->mousePressed = mousePressed;
}

void UrmButton::ResetBools()
{
	mouseOver = false;
	mousePressed = false;
}

void UrmButton::UpdateProperties()
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

void UrmButton::Render(sf::RenderTarget* renderTarget)
{
	sprites[index]->setPosition(x, y);
	sprites[index]->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*sprites[index]);
}
