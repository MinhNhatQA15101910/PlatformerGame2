#include "Level.h"

Level::Level(int** lvlData, int lvlDataWidth, int lvlDataHeight)
{
	this->lvlData = lvlData;
	this->lvlDataWidth = lvlDataWidth;
	this->lvlDataHeight = lvlDataHeight;
}

Level::~Level()
{
	delete lvlData;
}

int Level::GetSpriteIndex(int x, int y)
{
	return lvlData[y][x];
}

int** Level::GetLvlData()
{
	return lvlData;
}

int Level::GetLvlDataWidth()
{
	return lvlDataWidth;
}

int Level::GetLvlDataHeight()
{
	return lvlDataHeight;
}
