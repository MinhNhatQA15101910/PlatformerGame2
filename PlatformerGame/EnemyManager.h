#pragma once

#include "Crabby.h"
#include "LoadSave.h"

class EnemyManager
{
private:
	sf::Texture* crabbyTexture;
	sf::Sprite* crabbySprites[5][9];
	std::vector<Crabby*>* crabbies = new std::vector<Crabby*>();

	void LoadEnemySprites();
	void AddEnemies();
	void DrawCrabs(sf::RenderTarget* renderTarget, float xLvlOffset);

public:
	EnemyManager();
	~EnemyManager();

	void UpdateProperties(Level* level);

	void Render(sf::RenderTarget* renderTarget, float xLvlOffset);
};

