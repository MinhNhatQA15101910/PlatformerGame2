#include "PauseOverlay.h"

void PauseOverlay::LoadBackground()
{
	backgroundTexture = LoadSave::GetTextureAtlas(PAUSE_BACKGROUND);

	backgroundSprite = new sf::Sprite();
	backgroundSprite->setTexture(*backgroundTexture);

	bgW = (int)(backgroundTexture->getSize().x * SCALE);
	bgH = (int)(backgroundTexture->getSize().y * SCALE);
	bgX = (int)(GAME_WIDTH / 2 - bgW / 2);
	bgY = (int)(25 * SCALE);
}

void PauseOverlay::CreateSoundButtons()
{
	float soundX = 450 * SCALE;
	float musicY = 140 * SCALE;
	float sfxY = 186 * SCALE;

	musicButton = new SoundButton(soundX, musicY, SOUND_SIZE, SOUND_SIZE);
	sfxButton = new SoundButton(soundX, sfxY, SOUND_SIZE, SOUND_SIZE);
}

void PauseOverlay::CreateUrmButtons()
{
	float menuX = 313 * SCALE;
	float replayX = 387 * SCALE;
	float unpauseX = 462 * SCALE;
	float bY = 325 * SCALE;

	menuB = new UrmButton(menuX, bY, URM_SIZE, URM_SIZE, 2);
	replayB = new UrmButton(replayX, bY, URM_SIZE, URM_SIZE, 1);
	unpauseB = new UrmButton(unpauseX, bY, URM_SIZE, URM_SIZE, 0);
}

void PauseOverlay::CreateVolumeButton()
{
	float vX = 309 * SCALE;
	float vY = 278 * SCALE;
	volumeButton = new VolumeButton(vX, vY, SLIDER_WIDTH, VOLUME_HEIGHT);
}

bool PauseOverlay::IsIn(sf::Event::MouseButtonEvent e, PauseButton* b)
{
	return b->GetBounds()->getGlobalBounds().contains(sf::Vector2f((float)e.x, (float)e.y));
}

bool PauseOverlay::IsIn(sf::Event::MouseMoveEvent e, PauseButton* b)
{
	return b->GetBounds()->getGlobalBounds().contains(sf::Vector2f((float)e.x, (float)e.y));
}

PauseOverlay::PauseOverlay(int* gamestate, bool* paused)
{
	this->gamestate = gamestate;
	this->paused = paused;
	LoadBackground();
	CreateSoundButtons();
	CreateUrmButtons();
	CreateVolumeButton();
}

PauseOverlay::~PauseOverlay()
{
	delete backgroundTexture;
	delete backgroundSprite;
	delete musicButton;
	delete sfxButton;
	delete menuB;
	delete replayB;
	delete unpauseB;
	delete volumeButton;
}

void PauseOverlay::MouseButtonPressed(sf::Event* event)
{
	if (IsIn(event->mouseButton, musicButton))
	{
		musicButton->SetMousePressed(true);
	}
	else if (IsIn(event->mouseButton, sfxButton))
	{
		sfxButton->SetMousePressed(true);
	}
	else if (IsIn(event->mouseButton, menuB))
	{
		menuB->SetMousePressed(true);
	}
	else if (IsIn(event->mouseButton, replayB))
	{
		replayB->SetMousePressed(true);
	}
	else if (IsIn(event->mouseButton, unpauseB))
	{
		unpauseB->SetMousePressed(true);
	}
	else if (IsIn(event->mouseButton, volumeButton))
	{
		volumeButton->SetMousePressed(true);
	}
}

void PauseOverlay::MouseButtonReleased(sf::Event* event)
{
	if (IsIn(event->mouseButton, musicButton))
	{
		if (musicButton->IsMousePressed())
		{
			musicButton->SetMuted(!musicButton->IsMuted());
		}
	}
	else if (IsIn(event->mouseButton, sfxButton))
	{
		if (sfxButton->IsMousePressed())
		{
			sfxButton->SetMuted(!sfxButton->IsMuted());
		}
	}
	else if (IsIn(event->mouseButton, menuB))
	{
		if (menuB->IsMousePressed())
		{
			*gamestate = Constants::Gamestate::MENU;
			*paused = false;
		}
	}
	else if (IsIn(event->mouseButton, replayB))
	{
		if (replayB->IsMousePressed())
		{
			std::cout << "Replay lvl!\n";
		}
	}
	else if (IsIn(event->mouseButton, unpauseB))
	{
		if (unpauseB->IsMousePressed())
		{
			*paused = false;
		}
	}

	musicButton->ResetBools();
	sfxButton->ResetBools();
	menuB->ResetBools();
	replayB->ResetBools();
	unpauseB->ResetBools();
	volumeButton->ResetBools();
}

void PauseOverlay::MouseMoved(sf::Event* event)
{
	musicButton->SetMouseOver(false);
	sfxButton->SetMouseOver(false);
	menuB->SetMouseOver(false);
	replayB->SetMouseOver(false);
	unpauseB->SetMouseOver(false);
	volumeButton->SetMouseOver(false);

	if (IsIn(event->mouseMove, musicButton))
	{
		musicButton->SetMouseOver(true);
	}
	else if (IsIn(event->mouseMove, sfxButton))
	{
		sfxButton->SetMouseOver(true);
	}
	else if (IsIn(event->mouseMove, menuB))
	{
		menuB->SetMouseOver(true);
	}
	else if (IsIn(event->mouseMove, replayB))
	{
		replayB->SetMouseOver(true);
	}
	else if (IsIn(event->mouseMove, unpauseB))
	{
		unpauseB->SetMouseOver(true);
	}
	else if (IsIn(event->mouseMove, volumeButton))
	{
		volumeButton->SetMouseOver(true);
	}

	if (volumeButton->IsMousePressed())
	{
		volumeButton->ChangeX(event->mouseMove.x);
	}
}

void PauseOverlay::UpdateProperties()
{
	musicButton->UpdateProperties();;
	sfxButton->UpdateProperties();

	menuB->UpdateProperties();
	replayB->UpdateProperties();
	unpauseB->UpdateProperties();

	volumeButton->UpdateProperties();
}

void PauseOverlay::Render(sf::RenderTarget* renderTarget)
{
	// Background
	backgroundSprite->setPosition((float)bgX, (float)bgY);
	backgroundSprite->setScale(sf::Vector2f(SCALE, SCALE));
	renderTarget->draw(*backgroundSprite);

	// Sound buttons
	musicButton->Render(renderTarget);
	sfxButton->Render(renderTarget);

	// UrmButtons
	menuB->Render(renderTarget);
	replayB->Render(renderTarget);
	unpauseB->Render(renderTarget);

	// Volume button
	volumeButton->Render(renderTarget);
}
