#include "Enemy.h"

void Enemy::UpdateAnimationTick()
{
	aniTick++;
	if (aniTick >= aniSpeed)
	{
		aniTick = 0;
		aniIndex++;
		if (aniIndex >= Constants::EnemyConstants::GetSpriteAmount(enemyType, enemyState))
		{
			aniIndex = 0;
		}
	}
}

Enemy::Enemy(float x, float y, float width, float height, int enemyType)
	: Entity(x, y, width, height)
{
	this->enemyType = enemyType;
	InitHitbox(x, y, width, height);
}

Enemy::~Enemy()
{
}

int Enemy::GetAniIndex()
{
	return aniIndex;
}

int Enemy::GetEnemyState()
{
	return enemyState;
}

void Enemy::UpdateProperties()
{
	UpdateAnimationTick();
}
