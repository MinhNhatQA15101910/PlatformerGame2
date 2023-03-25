#pragma once

#include "Entity.h"
#include "HelpMethods.h"

class Enemy : public Entity
{
private:
	int aniIndex, enemyState, enemyType;
	int aniTick, aniSpeed = 25;
	bool firstUpdate = true;
	bool inAir;
	float fallSpeed;
	float gravity = 0.04f * SCALE;
	float walkSpeed = 0.35f * SCALE;
	int walkDir = Constants::Directions::LEFT;

	void UpdateAnimationTick();
	void UpdateMove(Level* level);

	void ChangeWalkDir();

public:
	Enemy(float x, float y, float width, float height, int enemyType);
	~Enemy();

	int GetAniIndex();
	int GetEnemyState();

	void UpdateProperties(Level* level);
};

