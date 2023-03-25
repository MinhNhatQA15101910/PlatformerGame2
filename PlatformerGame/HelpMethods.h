#pragma once

#include "Constants.h"
#include "Level.h"
#include <vector>

class HelpMethods
{
private:
	static bool IsSolid(float x, float y, Level* level)
	{
		float maxWidth = level->GetLvlDataWidth() * TILES_SIZE;
		if (x < 0 || x >= maxWidth)
		{
			return true;
		}
		if (y < 0 || y >= GAME_HEIGHT)
		{
			return true;
		}

		float xIndex = x / TILES_SIZE;
		float yIndex = y / TILES_SIZE;

		int value = level->GetLvlData()[(int)yIndex][(int)xIndex];

		if (value >= 48 || value < 0 || value != 11)
		{
			return true;
		}

		return false;
	}

public:
	static bool CanMoveHere(float x, float y, float width, float height, Level* level)
	{
		if (!IsSolid(x, y, level))
		{
			if (!IsSolid(x + width, y + height, level))
			{
				if (!IsSolid(x + width, y, level))
				{
					if (!IsSolid(x, y + height, level))
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

	static bool IsEntityOnFloor(sf::RectangleShape* hitbox, Level* level)
	{
		// Check the pixel below bottomleft and bottomright
		if (!IsSolid(
			hitbox->getPosition().x,
			hitbox->getPosition().y + hitbox->getSize().y + 1,
			level
		))
		{
			if (!IsSolid(
				hitbox->getPosition().x + hitbox->getSize().x,
				hitbox->getPosition().y + hitbox->getSize().y + 1,
				level
			))
			{
				return false;
			}
		}

		return true;
	}

	/*
	* We just check the bottomleft of the enemy here +/- the xSpeed. We never check bottom right in case the
	* enemy is going to the right. It would be more correct checking the bottomleft for left direction
	* and bottomright for the right direction. But it won't have big effect in the game. The enemy will simply change
	* direction sooner when there is an edge on the right side of the enemy, when it's going right.
	*/
	static bool IsFloor(sf::RectangleShape* hitbox, float xSpeed, Level* level)
	{
		return IsSolid(
			hitbox->getPosition().x + xSpeed, 
			hitbox->getPosition().y + hitbox->getSize().y + 1,
			level
		);
	}
};