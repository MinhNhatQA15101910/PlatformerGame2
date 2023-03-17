#pragma once

#include "Entity.h"
#include "EventHandler.h"
#include "Constants.h"
#include "LoadSave.h"

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
	bool left, up, right, down;
	float playerSpeed = 2.0f;

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

	void UpdatePos();
	void UpdateAnimationTick();
	void ResetAniTick();
	void SetAnimation();

public:
	Player(float x, float y, float scaleX, float scaleY);
	~Player();

	void ResetDirBools();

	void UpdateEvents(sf::Event* event);
	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};