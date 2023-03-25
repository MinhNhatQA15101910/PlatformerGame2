#include "Crabby.h"

Crabby::Crabby(float x, float y)
	: Enemy(x, y, CRABBY_WIDTH, CRABBY_HEIGHT, Constants::EnemyConstants::Enemies::CRABBY)
{
	InitHitbox(x, y, (int)(32 * SCALE), (int)(19 * SCALE));
}

Crabby::~Crabby()
{
}
