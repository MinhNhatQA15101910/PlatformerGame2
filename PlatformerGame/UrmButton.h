#pragma once

#include "PauseButton.h"
#include "LoadSave.h"

class UrmButton : public PauseButton
{
private:
	sf::Texture* texture;
	sf::Sprite* sprites[3];
	int rowIndex, index;
	bool mouseOver, mousePressed;

	void LoadSprites();

public:
	UrmButton(float x, float y, float width, float height, int rowIndex);
	~UrmButton();

	bool IsMouseOver();
	bool IsMousePressed();

	void SetMouseOver(bool mouseOver);
	void SetMousePressed(bool mousePressed);
	void ResetBools();

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};

