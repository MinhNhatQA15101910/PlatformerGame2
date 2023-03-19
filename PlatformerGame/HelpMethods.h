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

	static float GetEntityXPosNextToWall(sf::RectangleShape* hitbox, float xSpeed)
	{
		int currentTile = (int)(hitbox->getPosition().x / TILES_SIZE);
		if (xSpeed > 0)
		{
			// Right
			float tileXPos = currentTile * TILES_SIZE;
			float xOffset = TILES_SIZE - hitbox->getSize().x;
			return tileXPos + xOffset - 1;
		}
		else 
		{
			// Left
			return currentTile * TILES_SIZE;
		}
	}

	static float GetEntityYPosUnderRoofOrAboveFloor(sf::RectangleShape* hitbox, float airSpeed)
	{
		int currentTile = (int)(hitbox->getPosition().y / TILES_SIZE);
		if (airSpeed > 0)
		{
			// Falling - touching floor
			float tileYPos = currentTile * TILES_SIZE;
			float yOffset = TILES_SIZE - hitbox->getSize().y;
			return tileYPos + yOffset - 1;
		}
		else
		{
			// Jumping
			return currentTile * TILES_SIZE;
		}
	}

	static bool IsEntityOnFloor(sf::RectangleShape* hitbox, int** lvlData)
	{
		// Check the pixel below bottomleft and bottomright
		if (!IsSolid(
			hitbox->getPosition().x,
			hitbox->getPosition().y + hitbox->getSize().y + 1,
			lvlData
		))
		{
			if (!IsSolid(
				hitbox->getPosition().x + hitbox->getSize().x,
				hitbox->getPosition().y + hitbox->getSize().y + 1,
				lvlData
			))
			{
				return false;
			}
		}

		return true;
	}
};