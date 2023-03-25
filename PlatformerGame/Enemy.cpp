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

void Enemy::UpdateMove(Level* level)
{
	if (firstUpdate)
	{
		if (!HelpMethods::IsEntityOnFloor(hitbox, level))
		{
			inAir = true;
		}
		firstUpdate = false;
	}

	if (inAir)
	{
		if (HelpMethods::CanMoveHere(
			hitbox->getPosition().x,
			hitbox->getPosition().y + fallSpeed,
			hitbox->getSize().x,
			hitbox->getSize().y,
			level
			)
		)
		{
			hitbox->move(sf::Vector2f(0, fallSpeed));
			fallSpeed += gravity;
		}
		else
		{
			inAir = false;
			hitbox->setPosition(
				hitbox->getPosition().x,
				HelpMethods::GetEntityYPosUnderRoofOrAboveFloor(hitbox, fallSpeed)
			);
		}
	}
	else
	{
		switch (enemyState)
		{
		case Constants::EnemyConstants::EnemyStates::IDLE:
			enemyState = Constants::EnemyConstants::EnemyStates::RUNNING;
			break;
		case Constants::EnemyConstants::EnemyStates::RUNNING:
			float xSpeed = 0;

			if (walkDir == Constants::Directions::LEFT)
			{
				xSpeed = -walkSpeed;
			}
			else
			{
				xSpeed = walkSpeed;
			}

			if 
			(
				HelpMethods::CanMoveHere
				(
					hitbox->getPosition().x + xSpeed, 
					hitbox->getPosition().y,
					hitbox->getSize().x, 
					hitbox->getSize().y, 
					level
				)
			)
			{
				if (HelpMethods::IsFloor(hitbox, xSpeed, level))
				{
					hitbox->move(sf::Vector2f(xSpeed, 0));
					return;
				}
			}

			ChangeWalkDir();

			break;
		}
	}
}

void Enemy::ChangeWalkDir()
{
	if (walkDir == Constants::Directions::LEFT)
	{
		walkDir = Constants::Directions::RIGHT;
	}
	else
	{
		walkDir = Constants::Directions::LEFT;
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

void Enemy::UpdateProperties(Level* level)
{
	UpdateMove(level);
	UpdateAnimationTick();
}
