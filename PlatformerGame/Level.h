#pragma once
class Level
{
private:
	int lvlDataWidth, lvlDataHeight;
	int** lvlData;

public:
	Level(int** lvlData, int lvlDataWidth, int lvlDataHeight);
	~Level();

	int GetSpriteIndex(int x, int y);
	int** GetLvlData();
	int GetLvlDataWidth();
	int GetLvlDataHeight();
};

