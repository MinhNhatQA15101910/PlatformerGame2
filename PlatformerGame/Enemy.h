#pragma once

#include "Player.h"

class Enemy : public Entity
{
protected:
	int aniIndex, enemyState, enemyType;
	int aniTick, aniSpeed = 25;
	bool firstUpdate = true;
	bool inAir;
	float fallSpeed;
	float gravity = 0.04f * SCALE;
	float walkSpeed = 0.35f * SCALE;
	int walkDir = Constants::Directions::LEFT;
	int tileY;
	float attackDistance = TILES_SIZE;

	void TurnTowardsPlayer(Player* player);
	bool IsPlayerInRange(Player* player);
	bool IsPlayerCloseForAttack(Player* player);
	bool CanSeePlayer(Level* level, Player* player);

	void FirstUpdateCheck(Level* level);
	void UpdateInAir(Level* level);
	void Move(Level* level);

	void NewState(int enemyState);

	void UpdateAnimationTick();
	void ChangeWalkDir();

public:
	Enemy(float x, float y, float width, float height, int enemyType);
	~Enemy();

	int GetAniIndex();
	int GetEnemyState();
};

