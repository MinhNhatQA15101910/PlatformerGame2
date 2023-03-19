#pragma once
class Level
{
private:
	int** lvlData;

public:
	Level(int** lvlData);
	~Level();

	int GetSpriteIndex(int x, int y);
	int** GetLvlData();
};

