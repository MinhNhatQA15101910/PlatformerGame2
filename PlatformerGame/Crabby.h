#pragma once

#include "Enemy.h"

class Crabby : public Enemy
{
private:
	void UpdateMove(Level* level, Player* player);

public:
	Crabby(float x, float y);
	~Crabby();

	void UpdateProperties(Level* level, Player* player);
};