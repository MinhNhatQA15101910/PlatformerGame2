#pragma once

#include <SFML/Graphics.hpp>

#include "LoadSave.h"
#include "Constants.h"

class LevelManager
{
private:
	sf::Texture* texture;
	sf::Sprite* levelSprite[48];
	Level* levelOne;

	void ImportOutsideSprites();

public:
	LevelManager();
	~LevelManager();

	Level* GetCurrentLevel();

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget, float lvlOffset);
};

