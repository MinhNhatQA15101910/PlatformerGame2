#pragma once

#include "Entity.h"
#include "EventHandler.h"
#include "LoadSave.h"
#include "HelpMethods.h"

class Player : private Entity, private EventHandler
{
private:
	// Engine
	sf::Event* event;

	// Core
	sf::Texture* texture;
	int animationSize = 9, spriteSize = 6;
	sf::Sprite* animations[9][6];
	int aniTick, aniIndex, aniSpeed = 25;
	int playerAction = Constants::PlayerConstants::PlayerStates::IDLE;
	bool moving = false, attacking = false;
	bool left, up, right, down, jump;
	float playerSpeed = 2.0f;
	int** lvlData; 
	float xDrawOffset = 21 * SCALE;
	float yDrawOffset = 4 * SCALE;

	// Jumping / Gravity
	float airSpeed = 0.f;
	float gravity = 0.04f * SCALE;
	float jumpSpeed = -2.25f * SCALE;
	float fallSpeedAfterCollision = 0.5f * SCALE;
	bool inAir = false;

	// Key handler
	void KeyReleased();
	void KeyPressed();

	void KeyEventHandler();

	// Mouse button handler
	void MouseButtonPressed();
	void MouseButtonReleased();

	void MouseButtonEventHandler();

	// Mouse move handler
	void MouseEntered();
	void MouseLeft();
	void MouseMoved();

	void MouseMoveEventHandler();

	// Engine
	void LoadAnimations();

	void ResetInAir();
	void Jump();

	void UpdatePos();
	void UpdateXPos(float xSpeed);
	void UpdateAnimationTick();
	void ResetAniTick();
	void SetAnimation();

public:
	Player(float x, float y, float scaleX, float scaleY);
	~Player();

	void ResetDirBools();
	void LoadLvlData(int** lvlData);

	void UpdateEvents(sf::Event* event);
	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};