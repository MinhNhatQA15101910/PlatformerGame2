#include "Level.h"

Level::Level(int** lvlData)
{
	this->lvlData = lvlData;
}

Level::~Level()
{
	delete lvlData;
}

int Level::GetSpriteIndex(int x, int y)
{
	return lvlData[y][x];
}
