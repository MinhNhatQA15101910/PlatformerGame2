#include "Crabby.h"

Crabby::Crabby(float x, float y)
	: Enemy(x, y, CRABBY_WIDTH, CRABBY_HEIGHT, Constants::EnemyConstants::Enemies::CRABBY)
{
}

Crabby::~Crabby()
{
}
