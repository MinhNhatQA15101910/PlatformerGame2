#include "Enemy.h"

void Enemy::FirstUpdateCheck(Level* level)
{
	if (!HelpMethods::IsEntityOnFloor(hitbox, level))
	{
		inAir = true;
	}
	firstUpdate = false;
}

void Enemy::UpdateInAir(Level* level)
{
	if (HelpMethods::CanMoveHere(
		hitbox->getPosition().x,
		hitbox->getPosition().y + fallSpeed,
		hitbox->getSize().x,
		hitbox->getSize().y,
		level
	))
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
		tileY = (int)(hitbox->getPosition().y / TILES_SIZE);
	}
}

void Enemy::Move(Level* level)
{
	float xSpeed = 0;

	if (walkDir == Constants::Directions::LEFT)
	{
		xSpeed = -walkSpeed;
	}
	else
	{
		xSpeed = walkSpeed;
	}

	if (HelpMethods::CanMoveHere(
		hitbox->getPosition().x + xSpeed,
		hitbox->getPosition().y,
		hitbox->getSize().x,
		hitbox->getSize().y,
		level
	))
	{
		if (HelpMethods::IsFloor(hitbox, xSpeed, level))
		{
			hitbox->move(sf::Vector2f(xSpeed, 0));
			return;
		}
	}

	ChangeWalkDir();
}

void Enemy::NewState(int enemyState)
{
	this->enemyState = enemyState;
	aniTick = 0;
	aniIndex = 0;
}

void Enemy::TurnTowardsPlayer(Player* player)
{
	if (player->GetHitbox()->getPosition().x > hitbox->getPosition().x)
	{
		walkDir = Constants::Directions::RIGHT;
	}
	else
	{
		walkDir = Constants::Directions::LEFT;
	}
}

bool Enemy::IsPlayerInRange(Player* player)
{
	int absValue = (int)abs(player->GetHitbox()->getPosition().x - hitbox->getPosition().x);

	return (absValue <= attackDistance * 5);
}

bool Enemy::IsPlayerCloseForAttack(Player* player)
{
	int absValue = (int)abs(player->GetHitbox()->getPosition().x - hitbox->getPosition().x);

	return (absValue <= attackDistance);
}

bool Enemy::CanSeePlayer(Level* level, Player* player)
{
	int playerTileY = (int)(player->GetHitbox()->getPosition().y / TILES_SIZE);
	{
		if (playerTileY == tileY)
		{
			if (IsPlayerInRange(player))
			{
				if (HelpMethods::IsSightClear(level, hitbox, player->GetHitbox(), tileY))
				{
					return true;
				}
			}
		}

		return false;
	}
}

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
			if (enemyState == Constants::EnemyConstants::EnemyStates::ATTACK)
			{
				enemyState = Constants::EnemyConstants::EnemyStates::IDLE;
			}
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