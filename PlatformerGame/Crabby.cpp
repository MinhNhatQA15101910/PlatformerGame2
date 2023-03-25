#include "Crabby.h"

void Crabby::UpdateMove(Level* level, Player* player)
{
	if (firstUpdate)
	{
		FirstUpdateCheck(level);
	}

	if (inAir)
	{
		UpdateInAir(level);
	}
	else
	{
		switch (enemyState)
		{
		case Constants::EnemyConstants::EnemyStates::IDLE:
			NewState(Constants::EnemyConstants::EnemyStates::RUNNING);
			break;
		case Constants::EnemyConstants::EnemyStates::RUNNING:
			if (CanSeePlayer(level, player))
			{
				TurnTowardsPlayer(player);
			}
			if (IsPlayerCloseForAttack(player))
			{
				NewState(Constants::EnemyConstants::EnemyStates::ATTACK);
			}

			Move(level);
			break;
		}
	}
}

Crabby::Crabby(float x, float y)
	: Enemy(x, y, CRABBY_WIDTH, CRABBY_HEIGHT, Constants::EnemyConstants::Enemies::CRABBY)
{
	InitHitbox(x, y, (int)(32 * SCALE), (int)(19 * SCALE));
}

Crabby::~Crabby()
{
}

void Crabby::UpdateProperties(Level* level, Player* player)
{
	UpdateMove(level, player);
	UpdateAnimationTick();
}
