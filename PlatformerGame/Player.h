#pragma once

#include "Entity.h"
#include "LoadSave.h"
#include "HelpMethods.h"

class Player : public Entity
{
private:
	// Core
	sf::Texture* texture;
	int animationSize = 9, spriteSize = 6;
	sf::Sprite* animations[9][6];
	int aniTick, aniIndex, aniSpeed = 25;
	int playerAction = Constants::PlayerConstants::PlayerStates::IDLE;
	bool moving = false, attacking = false;
	bool left, up, right, down, jump;
	float playerSpeed = 1.0f * SCALE;
	Level* level;
	float xDrawOffset = 21 * SCALE;
	float yDrawOffset = 4 * SCALE;

	// Jumping / Gravity
	float airSpeed = 0.f;
	float gravity = 0.04f * SCALE;
	float jumpSpeed = -2.25f * SCALE;
	float fallSpeedAfterCollision = 0.5f * SCALE;
	bool inAir = false;

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
	Player(float x, float y, float width, float height);
	~Player();

	void ResetDirBools();
	void LoadLvlData(Level* level);

	void SetLeft(bool left);
	void SetRight(bool right);
	void SetJump(bool jump);
	void SetAttacking(bool attacking);

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget, float lvlOffset);
};