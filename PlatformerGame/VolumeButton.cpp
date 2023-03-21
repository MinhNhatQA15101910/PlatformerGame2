#include "VolumeButton.h"

void VolumeButton::LoadSprites()
{
	texture = LoadSave::GetTextureAtlas(VOLUME_BUTTONS);
	for (int i = 0; i < 3; i++)
	{
		sprites[i] = new sf::Sprite();
		sprites[i]->setTexture(*texture);
		sprites[i]->setTextureRect(sf::IntRect(
			i * VOLUME_DEFAULT_WIDTH, 
			0, 
			VOLUME_DEFAULT_WIDTH, 
			VOLUME_DEFAULT_HEIGHT
		));
	}

	slider = new sf::Sprite();
	slider->setTexture(*texture);
	slider->setTextureRect(sf::IntRect(
		3 * VOLUME_DEFAULT_WIDTH, 
		0, 
		SLIDER_DEFAULT_WIDTH, 
		VOLUME_DEFAULT_HEIGHT
	));
}

VolumeButton::VolumeButton(float x, float y, float width, float height)
	: PauseButton(x + width / 2, y, VOLUME_WIDTH, height)
{
	bounds->setPosition(
		bounds->getPosition().x - VOLUME_WIDTH / 2, 
		bounds->getPosition().y
	);
	buttonX = (int)(x + width / 2);
	this->x = x;
	this->width = width;
	minX = (int)(x + VOLUME_WIDTH / 2);
	maxX = (int)(x + width - VOLUME_WIDTH / 2);
	LoadSprites();
}

VolumeButton::~VolumeButton()
{
	delete texture;
	for (int i = 0; i < 3; i++)
	{
		delete sprites[i];
	}
	delete slider;
}

bool VolumeButton::IsMouseOver()
{
	return mouseOver;
}

bool VolumeButton::IsMousePressed()
{
	return mousePressed;
}

void VolumeButton::SetMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

void VolumeButton::SetMousePressed(bool mousePressed)
{
	this->mousePressed = mousePressed;
}

void VolumeButton::ChangeX(int x)
{
	if (x < minX)
	{
		buttonX = minX;
	}
	else if (x > maxX)
	{
		buttonX = maxX;
	}
	else
	{
		buttonX = x;
	}

	bounds->setPosition(
		(float)(buttonX - VOLUME_WIDTH / 2), 
		bounds->getPosition().y
	);
}

void VolumeButton::ResetBools()
{
	mouseOver = false;
	mousePressed = false;
}

void VolumeButton::UpdateProperties()
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

void VolumeButton::Render(sf::RenderTarget* renderTarget)
{
	slider->setPosition(x, y);
	slider->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*slider);

	sprites[index]->setPosition((float)(buttonX - VOLUME_WIDTH / 2), (float)y);
	sprites[index]->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*sprites[index]);
}
