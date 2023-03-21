#pragma once

#include <SFML/Graphics.hpp>

#include "LoadSave.h"

class MenuButton
{
private:
	int xPos, yPos, rowIndex, index;
	int xOffsetCenter = B_WIDTH / 2;
	int* gamestate;
	int gamestateValue;
	sf::Texture* texture;
	int spritesLength = 3;
	sf::Sprite* sprites[3];
	bool mouseOver, mousePressed;
	sf::RectangleShape* bounds;

	void LoadSprites();
	void InitBounds();

public:
	MenuButton(int xPos, int yPos, int rowIndex, int* gamestate, int gamestateValue);
	~MenuButton();

	bool IsMouseOver();
	bool IsMousePressed();
	sf::RectangleShape* GetBounds();

	void SetMouseOver(bool mouseOver);
	void SetMousePressed(bool mousePressed);
	void ApplyGamestate();
	void ResetBools();

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};

