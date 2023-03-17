#include "LevelManager.h"

void LevelManager::ImportOutsideSprites()
{
	texture = LoadSave::GetTextureAtlas(LEVEL_ATLAS);
	
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 12; i++)
		{
			int index = j * 12 + i;

			levelSprite[index] = new sf::Sprite();
			levelSprite[index]->setTexture(*texture);
			levelSprite[index]->setTextureRect(sf::IntRect(i * 32, j * 32, 32, 32));
		}
	}
}

LevelManager::LevelManager()
{
	ImportOutsideSprites();
	levelOne = new Level(LoadSave::GetLevelData());
}

LevelManager::~LevelManager()
{
	delete levelOne;
	for (int i = 0; i < 48; i++) 
		delete levelSprite[i];
	delete texture;
}

void LevelManager::UpdateProperties()
{
}

void LevelManager::Render(sf::RenderTarget* renderTarget)
{
	for (int j = 0; j < TILES_IN_HEIGHT; j++)
	{
		for (int i = 0; i < TILES_IN_WIDTH; i++)
		{
			int index = levelOne->GetSpriteIndex(i, j);

			levelSprite[index]->setPosition(i * TILES_SIZE, j * TILES_SIZE);
			levelSprite[index]->setScale(sf::Vector2f(SCALE, SCALE));
			renderTarget->draw(*levelSprite[index]);
		}
	}
}
