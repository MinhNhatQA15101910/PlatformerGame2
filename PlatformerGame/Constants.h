#pragma once

const std::string WINDOW_TITLE = "Platformer Game";
const int FRAMERATE_LIMIT = 180;

// Game framework
const int FPS_SET = 120;
const int UPS_SET = 200;

// Game Window
const int TILES_DEFAULT_SIZE = 32;
const float SCALE = 2.0f;
const int TILES_IN_WIDTH = 26;
const int TILES_IN_HEIGHT = 14;
const float TILES_SIZE = (TILES_DEFAULT_SIZE * SCALE);
const float GAME_WIDTH = (TILES_SIZE * TILES_IN_WIDTH);
const float GAME_HEIGHT = (TILES_SIZE * TILES_IN_HEIGHT);

// UI
const int B_WIDTH_DEFAULT = 140;
const int B_HEIGHT_DEFAULT = 56;
const int B_WIDTH = (int)(B_WIDTH_DEFAULT * SCALE);
const int B_HEIGHT = (int)(B_HEIGHT_DEFAULT * SCALE);

// Pause Buttons
const int SOUND_SIZE_DEFAULT = 42;
const int SOUND_SIZE = (int)(SOUND_SIZE_DEFAULT * SCALE);

// URM Buttons
const int URM_DEFAULT_SIZE = 56;
const int URM_SIZE = (int)(URM_DEFAULT_SIZE * SCALE);

// Volume Buttons
const int VOLUME_DEFAULT_WIDTH = 28;
const int VOLUME_DEFAULT_HEIGHT = 44;
const int SLIDER_DEFAULT_WIDTH = 215;
const int VOLUME_WIDTH = (int)(VOLUME_DEFAULT_WIDTH * SCALE);
const int VOLUME_HEIGHT = (int)(VOLUME_DEFAULT_HEIGHT * SCALE);
const int SLIDER_WIDTH = (int)(SLIDER_DEFAULT_WIDTH * SCALE);

// Resource
const std::string RES_FOLDER = "res";

const std::string ICON_IMAGE = "brick.png";
const std::string PLAYER_ATLAS = "player_sprites.png";
const std::string LEVEL_ATLAS = "outside_sprites.png";
//const std::string LEVEL_ONE_DATA = "level_one_data.png";
const std::string LEVEL_ONE_DATA = "level_one_data_long.png";
const std::string MENU_BUTTONS = "button_atlas.png";
const std::string MENU_BACKGROUND = "menu_background.png";
const std::string PAUSE_BACKGROUND = "pause_menu.png";
const std::string SOUND_BUTTONS = "sound_button.png";
const std::string URM_BUTTONS = "urm_buttons.png";
const std::string VOLUME_BUTTONS = "volume_buttons.png";
const std::string MENU_BACKGROUND_IMG = "background_menu.png";

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

	enum Gamestate
	{
		PLAYING = 0,
		MENU = 1,
		OPTIONS = 2,
		QUIT = 3
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

