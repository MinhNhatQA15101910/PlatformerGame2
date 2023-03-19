#pragma once

#include "Constants.h"

class HelpMethods
{
private:
	static bool IsSolid(float x, float y, int** lvlData)
	{
		if (x < 0 || x >= GAME_WIDTH)
		{
			return true;
		}
		if (y < 0 || y >= GAME_HEIGHT)
		{
			return true;
		}

		float xIndex = x / TILES_SIZE;
		float yIndex = y / TILES_SIZE;

		int value = lvlData[(int)yIndex][(int)xIndex];

		if (value >= 48 || value < 0 || value != 11)
		{
			return true;
		}

		return false;
	}

public:
	static bool CanMoveHere(float x, float y, float width, float height, int** lvlData)
	{
		if (!IsSolid(x, y, lvlData))
		{
			if (!IsSolid(x + width, y + height, lvlData))
			{
				if (!IsSolid(x + width, y, lvlData))
				{
					if (!IsSolid(x, y + height, lvlData))
					{
						return true;
					}
				}
			}
		}

		return false;
	}
};