#pragma once

#include "SoundButton.h"
#include "UrmButton.h"
#include "VolumeButton.h"

class PauseOverlay
{
private:
	int* gamestate;
	bool* paused;
	sf::Texture* backgroundTexture;
	sf::Sprite* backgroundSprite;
	int bgX, bgY, bgW, bgH;
	SoundButton* musicButton, *sfxButton;
	UrmButton* menuB, * replayB, * unpauseB;
	VolumeButton* volumeButton;

	void LoadBackground();
	void CreateSoundButtons();
	void CreateUrmButtons();
	void CreateVolumeButton();

	bool IsIn(sf::Event::MouseButtonEvent e, PauseButton* b);
	bool IsIn(sf::Event::MouseMoveEvent e, PauseButton* b);

public:
	PauseOverlay(int* gamestate, bool* paused);
	~PauseOverlay();

	void MouseButtonPressed(sf::Event* event);
	void MouseButtonReleased(sf::Event* event);
	void MouseMoved(sf::Event* event);

	void UpdateProperties();

	void Render(sf::RenderTarget* renderTarget);
};

