#pragma once

#include "PauseButton.h"
#include "LoadSave.h"

class VolumeButton : public PauseButton
{
private:
	sf::Texture* texture;
	sf::Sprite* sprites[3];
	sf::Sprite* slider;
	int index = 0;
	bool mouseOver, mousePressed;
	int buttonX, minX, maxX;

	void LoadSprites();

public:
	VolumeButton(float x, float y, float width, float height);
	~VolumeButton();

	bool IsMouseOver();
	bool IsMousePressed();

	void SetMouseOver(bool mouseOver);
	void SetMousePressed(bool mousePressed);

	void ChangeX(int x);
	void ResetBools();

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};

