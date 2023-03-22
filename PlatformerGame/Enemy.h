#pragma once

#include "Entity.h"
#include "Constants.h"

class Enemy : public Entity
{
private:
	int aniIndex, enemyState, enemyType;
	int aniTick, aniSpeed = 25;

	void UpdateAnimationTick();

public:
	Enemy(float x, float y, float width, float height, int enemyType);
	~Enemy();

	int GetAniIndex();
	int GetEnemyState();

	void UpdateProperties();
};

