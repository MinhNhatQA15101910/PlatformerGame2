#include "SoundButton.h"

void SoundButton::LoadSoundTextures()
{
	soundTexture = LoadSave::GetTextureAtlas(SOUND_BUTTONS);

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			soundSprites[j][i] = new sf::Sprite();
			soundSprites[j][i]->setTexture(*soundTexture);
			soundSprites[j][i]->setTextureRect(
				sf::IntRect(
					i * SOUND_SIZE_DEFAULT, 
					j * SOUND_SIZE_DEFAULT, 
					SOUND_SIZE_DEFAULT, 
					SOUND_SIZE_DEFAULT
				)
			);
		}
	}
}

SoundButton::SoundButton(float x, float y, float width, float height)
	: PauseButton(x, y, width, height)
{
	LoadSoundTextures();
}

SoundButton::~SoundButton()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete soundSprites[i][j];
		}
	}
	delete soundTexture;
}

void SoundButton::ResetBools()
{
	mouseOver = false;
	mousePressed = false;
}

bool SoundButton::IsMouseOver()
{
	return mouseOver;
}

bool SoundButton::IsMousePressed()
{
	return mousePressed;
}

bool SoundButton::IsMuted()
{
	return muted;
}

void SoundButton::SetMouseOver(bool mouseOver)
{
	this->mouseOver = mouseOver;
}

void SoundButton::SetMousePressed(bool mousePressed)
{
	this->mousePressed = mousePressed;
}

void SoundButton::SetMuted(bool muted)
{
	this->muted = muted;
}

void SoundButton::UpdateProperties()
{
	if (muted)
	{
		rowIndex = 1;
	}
	else 
	{
		rowIndex = 0;
	}

	colIndex = 0;
	if (mouseOver)
	{
		colIndex = 1;
	}
	if (mousePressed)
	{
		colIndex = 2;
	}
}

void SoundButton::Render(sf::RenderTarget* renderTarget)
{
	soundSprites[rowIndex][colIndex]->setPosition(x, y);
	soundSprites[rowIndex][colIndex]->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*soundSprites[rowIndex][colIndex]);
}
