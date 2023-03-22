#pragma once

#include "Player.h"
#include "LevelManager.h"
#include "Statemethods.h"
#include "State.h"
#include "EventHandler.h"
#include "PauseOverlay.h"
#include "EnemyManager.h"

class Playing : public State, public Statemethods, public EventHandler
{
private:
	sf::Event* event;

	Player* player;
	LevelManager* levelManager;
	EnemyManager* enemyManager;
	PauseOverlay* pauseOverlay;
	bool paused = false;

	float xLvlOffset;
	float leftBorder = 0.2f * GAME_WIDTH;
	float rightBorder = 0.8f * GAME_WIDTH;
	float lvlTilesWide = (float)(LoadSave::GetLevelData()->GetLvlDataWidth());
	float maxTilesOffset = lvlTilesWide - TILES_IN_WIDTH;
	float maxLvlOffsetX = maxTilesOffset * TILES_SIZE;

	sf::Texture* backgroundTexture, * bigCloudTexture, * smallCloudTexture;
	sf::Sprite* backgroundSprite, * bigCloudSprites[3], * smallCloudSprites[8];
	float smallCloudsPos[8];

	void InitClasses();

	void CheckCloseToBorder();

	// Key handler
	void KeyReleased();
	void KeyPressed();

	// Mouse button handler
	void MouseButtonPressed();
	void MouseButtonReleased();

	// Mouse move handler
	void MouseEntered();
	void MouseLeft();
	void MouseMoved();

public:
	Playing(int* gamestate);
	~Playing();

	Player* GetPlayer();

	void UpdateProperties();
	void UpdateEvents(sf::Event* event);

	void RenderClouds(sf::RenderTarget* renderTarget);
	void Render(sf::RenderTarget* renderTarget);

	void KeyEventHandler();
	void MouseButtonEventHandler();
	void MouseMoveEventHandler();
	void WindowFocusLost();
};

