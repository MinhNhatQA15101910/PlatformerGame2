#include "EnemyManager.h"

void EnemyManager::LoadEnemySprites()
{
	crabbyTexture = LoadSave::GetTextureAtlas(CRABBY_SPRITE);
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			crabbySprites[j][i] = new sf::Sprite();
			crabbySprites[j][i]->setTexture(*crabbyTexture);
			crabbySprites[j][i]->setTextureRect(sf::IntRect(
				i * CRABBY_WIDTH_DEFAULT, 
				j * CRABBY_HEIGHT_DEFAULT, 
				CRABBY_WIDTH_DEFAULT, 
				CRABBY_HEIGHT_DEFAULT
			));
		}
	}
}

void EnemyManager::AddEnemies()
{
	crabbies = LoadSave::GetCrabs();
}

void EnemyManager::DrawCrabs(sf::RenderTarget* renderTarget, float xLvlOffset)
{
	for (Crabby* c : *crabbies)
	{
		crabbySprites[c->GetEnemyState()][c->GetAniIndex()]->setPosition(
			c->GetHitbox()->getPosition().x - xLvlOffset - CRABBY_DRAWOFFSET_X, 
			c->GetHitbox()->getPosition().y - CRABBY_DRAWOFFSET_Y
		);
		crabbySprites[c->GetEnemyState()][c->GetAniIndex()]->setScale(sf::Vector2f(SCALE, SCALE));
		renderTarget->draw(*crabbySprites[c->GetEnemyState()][c->GetAniIndex()]);
	}
}

EnemyManager::EnemyManager()
{
	LoadEnemySprites();
	AddEnemies();
}

EnemyManager::~EnemyManager()
{
	delete crabbyTexture;
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 9; i++)
		{
			delete crabbySprites[j][i];
		}
	}
	for (Crabby* c : *crabbies)
	{
		delete c;
	}
	delete crabbies;
}

void EnemyManager::UpdateProperties(Level* level)
{
	for (Crabby* c : *crabbies)
	{
		c->UpdateProperties(level);
	}
}

void EnemyManager::Render(sf::RenderTarget* renderTarget, float xLvlOffset)
{
	DrawCrabs(renderTarget, xLvlOffset);
}
