#pragma once

const int TILES_DEFAULT_SIZE = 32;
const float SCALE = 2.0f;
const int TILES_IN_WIDTH = 26;
const int TILES_IN_HEIGHT = 14;
const float TILES_SIZE = (TILES_DEFAULT_SIZE * SCALE);
const float GAME_WIDTH = (TILES_SIZE * TILES_IN_WIDTH);
const float GAME_HEIGHT = (TILES_SIZE * TILES_IN_HEIGHT);

class Constants
{
public:
	enum Directions
	{
		LEFT = 0,
		UP = 1,
		RIGHT = 2,
		DOWN = 3
	};

	class PlayerConstants
	{
	public:
		enum PlayerStates
		{
			IDLE = 0, 
			RUNNING = 1,
			JUMP = 2, 
			FALLING = 3, 
			GROUND = 4, 
			HIT = 5, 
			ATTACK_1 = 6,
			ATTACK_JUMP_1 = 7, 
			ATTACK_JUMP_2 = 8
		};

		static int GetSpriteAmount(int playerAction)
		{
			switch (playerAction) 
			{
			case PlayerStates::RUNNING:
				return 6;
			case PlayerStates::IDLE:
				return 5;
			case PlayerStates::HIT:
				return 4;
			case PlayerStates::JUMP:
			case PlayerStates::ATTACK_1:
			case PlayerStates::ATTACK_JUMP_1:
			case PlayerStates::ATTACK_JUMP_2:
				return 3;
			case PlayerStates::GROUND:
				return 2;
			case FALLING:
			default:
				return 1;
			}
		}
	};
};

